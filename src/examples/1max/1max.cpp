#include <cstdio>

int main(void) {
	TournamentSelection myStrategy();

	OneMaxFitnessFunction myFunction();
	TwoPointCrossover myCrossover();
	BitwiseMutation myMutation();

	NonHierarchicalGenePool<int> baseGenes[32];

	for (int i = 0; i < 32; i++) {
		baseGenes[i] = new NonHierarchicalGenePool<int>({0, 1}, 2);
	}

	Individual templateIndividual(baseGenes, myCrossover, myMutation, myFunction);

	HierarchicalGenePool topLevelPool(templateIndividual, 64, 100, 1);

	for (int i = 0; i < 1000; i++) {
		topLevelPool.runGenerations();
	}
}
