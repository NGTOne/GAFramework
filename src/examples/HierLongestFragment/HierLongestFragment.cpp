#include <cstdio>
#include <iostream>
#include <sstream>
#include <libHierGA/HierGA.hpp>
#include "HierLongestFragmentFitness.hpp"

using namespace std;

int main(void) {
	HierarchicalEA ea(100);
	vector<Locus*> baseLoci(8, new IntLocus(0, 1));
	vector<PopulationNode*> bottomNodes;
	vector<Locus*> populationLoci;

	for (int i = 0; i < 4; i++) {
		stringstream name;
		name << "P" << 5 - i;
		bottomNodes.push_back(new EANode(
			16,
			baseLoci,
			vector<ObjectiveFunction*>(
				{new HierLongestFragmentFitness()}
			),
			new HierLongestFragmentToString(),
			vector<EndCondition*>({new IterationCountEnd(100)}),
			name.str(),
			new GA(2, false, new TournamentSelection(0.95, 4)),
			new NPointCrossover(2),
			new UniformMutation(0.2)
		));
		populationLoci.push_back(new PopulationLocus(bottomNodes[i]));
	}

	ea.addNodes(bottomNodes, vector<bool>(4, false), vector<bool>(4, false));
	ea.addNode(
		new EANode(
			8,
			populationLoci,
			vector<ObjectiveFunction*>(
				{new HierLongestFragmentFitness()}
			),
			new HierLongestFragmentToString(),
			vector<EndCondition*>({new IterationCountEnd(100)}),
			"P1",
			new GA(2, false, new TournamentSelection(0.95, 4)),
			new NPointCrossover(2),
			new UniformMutation(0.2)
		),
		true,
		true
	);

	ea.setEvolutionOrder({"P5", "P4", "P3", "P2", "P1"});
	ea.run(true);
}

