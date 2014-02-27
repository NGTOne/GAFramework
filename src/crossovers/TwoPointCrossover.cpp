#include <random>

class TwoPointCrossover : CrossoverOperation {
	private:

	protected:
	unsigned seed;

	public:
	TwoPointCrossover(unsigned newSeed) : seed(newSeed);
	int[][] crossOver(int[] firstGenome, int[] secondGenome);


	int[][] crossOver(int[] firstGenome, int[] secondGenome) {
		int firstGenomeLength = sizeof(firstGenome)/sizeof(int);
		int secondGenomeLength = sizeof(secondGenome)/sizeof(int);
		int firstPoint;
		int secondPoint = 0;

		if (firstGenomeLength != secondGenomeLength) {
			return NULL;
		}

		int children[2][firstGenomeLength];

		mt19937 generator;
		uniform_int_distribution<int> distribution(0, firstGenomeLength);

		firstPoint = distribution(generator);
		
		while (secondPoint <= firstPoint) {
			secondPoint = distribution(generator);
		}
	}
}
