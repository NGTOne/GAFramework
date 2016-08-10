#include <cstdio>
#include <iostream>
#include <sstream>
#include <libHierGA/HierGA.hpp>
#include "1maxFitness.hpp"

using namespace std;

int main(void) {
	HierarchicalEA ea(100);

	ea.addConstructiveTree<EANode>(
		new LocusMultiplierPopFormula(2),
		{{}, vector<Locus*>(
			8,
			new NumericCollectionLocus<int>({0, 1})
		)},
		{{new OneMaxFitness()}, {new OneMaxFitness()}},
		{new OneMaxToString(), new OneMaxToString()},
		{{new IterationCountEnd(100)}, {new IterationCountEnd(100)}},
		TreeBuilder("P1").addSubNodes("P1", {"P2", "P3", "P4", "P5"}),
		{true, false},
		{true, false},
		new GA(
			2,
			false,
			new TournamentSelection(0.95, 4),
			new NPointCrossover(2),
			new UniformMutation(0.2)
		)
	);

	ea.setEvolutionOrder({"P5", "P4", "P3", "P2", "P1"});
	ea.run(true);
	ea.deleteAllNodes();
}

