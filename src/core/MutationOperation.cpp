//Abstract class for mutation operators. Lets us define any mutation operation we like.

#include <random>
#include <chrono>
#include "MutationOperation.h"

using namespace std;

MutationOperation::MutationOperation() {
	mutationRate = 0;
	seed = chrono::system_clock::now().time_since_epoch().count();
}

MutationOperation::MutationOperation(int newMutationRate) : mutationRate(newMutationRate) {
	seed = chrono::system_clock::now().time_since_epoch().count();
}

MutationOperation::MutationOperation(int newMutationRate, unsigned newSeed) : mutationRate(newMutationRate), seed(newSeed) {}
