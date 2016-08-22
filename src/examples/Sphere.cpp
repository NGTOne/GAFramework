#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "SphereFitness.hpp"

using namespace std;

int main(void) {
	HierarchicalEA ea(100);
	vector<Locus*> baseLoci(32, new NumericSetLocus<double>(-50, 50));
	ea.addNode<EANode>(
		6,
		baseLoci,
		{new SphereFitness()},
		new SphereToString(),
		{new IterationCountEnd(100)},
		"P1",
		true,
		true,
		new MuPlusLambdaES(
			new UniformCrossover(),
			6
		)
	);

	ea.setEvolutionOrder({"P1"});
	ea.run(true);

	ea.deleteAllNodes();
}

