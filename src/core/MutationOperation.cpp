//Abstract class for mutation operators. Lets us define any mutation operation we like.

#include <random>
#include <chrono>

class MutationOperation {
	private:

	protected:
	unsigned seed;
        int mutationRate;

	public:

	MutationOperation(int newMutationRate) : mutationRate(newMutationRate) {
		seed = chrono::system_clock::now().time_since_epoch().count();
	}

	MutationOperation(int newMutationRate unsigned newSeed) : mutationRate(newMutationRate), seed(newSeed) {}

	int[] mutate(int initialGenome[]);
}
