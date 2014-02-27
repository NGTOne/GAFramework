//This is an abstract class for crossover operations. Lets us define any 
//crossover we like, and use it for a given Individual.

#include <random>
#include <chrono>
using namespace std;

class CrossoverOperation {
	private:

	protected:
	unsigned seed;

	public:
	CrossoverOperation() {
		seed = chrono::system_clock::now().time_since_epoch().count();
	}
	
	CrossoverOperation(int newSeed, int newCrossoverRate) : seed(newSeed) {}

	int[][] crossOver(int genomeOne[], int genomeTwo[]);
}
