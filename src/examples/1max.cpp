#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "1maxFitness.hpp"

using namespace std;

int main(void) {
	HierarchicalEA ea(100);
	vector<Locus*> baseLoci(32, new IntLocus(0, 1));
	ea.addNode(
		new EANode(
			64,
			baseLoci,
			vector<ObjectiveFunction*>({new OneMaxFitness()}),
			new OneMaxToString(),
			vector<EndCondition*>({new IterationCountEnd(100)}),
			"P1",
			new GA(2, false, new TournamentSelection(0.95, 4)),
			new NPointCrossover(2),
			new UniformMutation(0.2)
		),
		true,
		true
	);

	ea.setEvolutionOrder({"P1"});
	ea.run(true);

	ea.deleteAllNodes();
}

