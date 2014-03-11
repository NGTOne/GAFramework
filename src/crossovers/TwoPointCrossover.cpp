#include <random>
#include <chrono>
using namespace std;

class TwoPointCrossover : CrossoverOperation {
	private:

	protected:
	
	public:
	
	int ** crossOver(int firstGenome[], int secondGenome[]) {
		int firstGenomeLength = sizeof(firstGenome)/sizeof(int);
		int secondGenomeLength = sizeof(secondGenome)/sizeof(int);
		int firstPoint = firstGenomeLength + 1;
		int secondPoint = 0;

		//If our parents are of different types, we're gonna have a
		//problem
		if (firstGenomeLength != secondGenomeLength) {
			return NULL;
		}

		//We're generating two children - each one uses the same
		//crossover points, but draws from the parents in a different
		//order
		int children[2][firstGenomeLength];

		mt19937 generator(seed);
		uniform_int_distribution<int> distribution(0, firstGenomeLength);
		//There's not much point in creating two clones of the parents,
		//is there?
		while (firstPoint >= firstGenomeLength) {
                	firstPoint = distribution(generator);
		}
		
		//Ensures that the second point is after the first one
		while (secondPoint <= firstPoint) {
			secondPoint = distribution(generator);
		}

		//If I've thought this through right, this should support
		//"coincidental" 1-point crossover - i.e. one of the points
		//lies on the extreme right or left, outside the array
		for (int i = 0; i < firstPoint; i++) {
			children[0][i] = firstGenome[i];
                        children[1][i] = secondGenome[i];
		}

		for (int i = firstPoint; i < secondPoint; i++) {
                        children[1][i] = firstGenome[i];
                        children[0][i] = secondGenome[i];
		}

		for (int i = secondPoint; i < firstGenomeLength; i++) {
                        children[0][i] = firstGenome[i];
                        children[1][i] = secondGenome[i];
		}

		return children;
	}
}
