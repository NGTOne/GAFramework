#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "LongestFragmentFitness.hpp"

using namespace std;

int main(void) {
	HierarchicalEA ea(100);
	vector<Locus*> baseLoci(32, new IntLocus(0, 1));

	ea.addNode<EANode>(
		64,
		baseLoci,
		{new LongestFragmentFitness()},
		new LongestFragmentToString(),
		{new IterationCountEnd(100)},
		"P1",
		true,
		true,
		new GA(
			2,
			false,
			new TournamentSelection(0.95, 4),
			new NPointCrossover(2),
			new UniformMutation(0.2)
		)
	);
	ea.setEvolutionOrder({"P1"});
	ea.run(true);
	ea.deleteAllNodes();
}

