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
	vector<Locus*> topLoci;

	for (int i = 0; i < 4; i++) {
		stringstream name;
		name << "P" << 2 + i;
		bottomNodes.push_back(new EANode(
			8,
			baseLoci,
			vector<ObjectiveFunction*>(),
			new LongestFragmentToString(),
			vector<EndCondition*>({new IterationCountEnd(100)}),
			name.str(),
			new GA(2, false, new TournamentSelection(0.95, 4)),
			new NPointCrossover(2),
			new UniformMutation(0.2)
		));
		topLoci.push_back(new PopulationLocus(bottomNodes[i]));
	}

	ea.addNodes(
		bottomNodes,
		vector<bool>(4, true),
		vector<bool>(4, false)
	);

	// Add context for the top node (to demonstrate)
	for (unsigned int i = 0; i < 16; i++)
		topLoci.push_back(new IntLocus(0, 1));

	ea.addNode(
		new EANode(
			8,
			topLoci,
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

	// Add the meta node
	std::vector<std::tuple<
		std::string,
		ApportionmentFunction *,
		AggregationFunction *
	>> hierarchyNodes;

	std::vector<std::string> nodes = {"P1", "P2", "P3", "P4", "P5"};
	for (unsigned int i = 0; i < nodes.size(); i++)
		hierarchyNodes.push_back(std::make_tuple(
			nodes[i],
			new LongestFragmentApportionment,
			new BestOfAggregator
		));

	ea.addMetaPopulation<EANode>(
		4,
		hierarchyNodes,
		{new LongestFragmentFitness()},
		new LongestFragmentToString,
		{new IterationCountEnd(100)},
		"M1",
		new GA(2, false, new TournamentSelection(0.95, 4)),
		new NPointCrossover(2),
		new UniformMutation(0.2)
	);

	ea.setEvolutionOrder({"M1", "P5", "P4", "P3", "P2", "P1"});
	ea.setNodesToPrint({"M1", "P1", "P2", "P3", "P4", "P5"});
	ea.run(true);
	ea.deleteAllNodes();
}

