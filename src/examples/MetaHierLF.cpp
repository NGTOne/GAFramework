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

	ea.addNodes(
		bottomNodes,
		vector<bool>(4, true),
		vector<bool>(4, false)
	);
	ea.addNode(
		new EANode(
			8,
			populationLoci,
			vector<ObjectiveFunction*>(),
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

	// TODO TODO: Refactor this call
	ea.addMetaPopulation(
		new EANode(
			8,
			vector<Locus*>(),
			vector<ObjectiveFunction*>(),
			NULL,
			vector<EndCondition*>({new IterationCountEnd(100)}),
			"M1",
			new GA(2, false, new TournamentSelection(0.95, 4)),
			new NPointCrossover(2),
			new UniformMutation(0.2)
		),
		{new LongestFragmentFitness()},
		new LongestFragmentToString(),
		"P1",
		make_tuple(
			new LongestFragmentApportionment,
			new BestOfAggregator
		),
		{
			make_tuple(
				"P2",
				new LongestFragmentApportionment,
				new BestOfAggregator
			),
			make_tuple(
				"P3",
				new LongestFragmentApportionment,
				new BestOfAggregator
			),
			make_tuple(
				"P4",
				new LongestFragmentApportionment,
				new BestOfAggregator
			),
			make_tuple(
				"P5",
				new LongestFragmentApportionment,
				new BestOfAggregator
			)
		}
	);

	vector<string> names({"P5", "P4", "P3", "P2"});
	for (unsigned int i = 0; i < names.size(); i++)
		ea.getNodeByName(names[i])->setObjective(new Apportionment(
			ea.getNodeByName("P1"),
			new LongestFragmentApportionment(),
			new BestOfAggregator(),
			1
		));

	ea.setEvolutionOrder({"P5", "P4", "P3", "P2", "P1"});
	ea.setNodesToPrint({"P1", "P2", "P3", "P4", "P5"});
	ea.run(true);
	ea.deleteAllNodes();
}

