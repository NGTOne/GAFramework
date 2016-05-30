#include <cstdio>
#include <iostream>
#include <sstream>
#include <libHierGA/HierGA.hpp>
#include "LongestFragmentFitness.hpp"

using namespace std;

int main(void) {
	HierarchicalEA ea(100);
	vector<Locus*> baseLoci(8, new IntLocus(0, 1));
	vector<PopulationNode*> bottomNodes;
	vector<Locus*> populationLoci;

	for (int i = 0; i < 4; i++) {
		stringstream name;
		name << "P" << 2 + i;
		bottomNodes.push_back(new EANode(
			16,
			baseLoci,
			vector<ObjectiveFunction*>(),
			new LongestFragmentToString(),
			vector<EndCondition*>({new IterationCountEnd(100)}),
			name.str(),
			new GA(2, false, new TournamentSelection(0.95, 4)),
			new NPointCrossover(2),
			new UniformMutation(0.2)
		));
		populationLoci.push_back(new PopulationLocus(bottomNodes[i]));
	}

	ea.addNodes(bottomNodes, vector<bool>(4, true), vector<bool>(4, false));
	ea.addNode(
		new EANode(
			8,
			populationLoci,
			vector<ObjectiveFunction*>(
				{new LongestFragmentFitness()}
			),
			new LongestFragmentToString(),
			vector<EndCondition*>({new IterationCountEnd(100)}),
			"P1",
			new GA(2, false, new TournamentSelection(0.95, 4)),
			new NPointCrossover(2),
			new UniformMutation(0.2)
		),
		true,
		true
	);

	vector<string> names({"P5", "P4", "P3", "P2"});
	for (int i = 0; i < names.size(); i++)
		ea.getNodeByName(names[i])->setObjective(new BestOfApportionment(
			ea.getNodeByName("P1"),
			new LongestFragmentApportionment()
		));

	ea.setEvolutionOrder({"P5", "P4", "P3", "P2", "P1"});
	ea.setNodesToPrint({"P1", "P2", "P3", "P4", "P5"});
	ea.run(true);
	ea.deleteAllNodes();
}

