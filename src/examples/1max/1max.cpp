#include <cstdio>

int main(void) {
	TournamentSelection myStrategy();

	OneMaxFitnessFunction myFunction();
	TwoPointCrossover myCrossover();
	BitwiseMutation myMutation();

	Individual templateIndividual(myFunction);
}
