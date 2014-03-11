//This is an abstract class for crossover operations. Lets us define any 
//crossover we like, and use it for a given Individual.

#include <random>
#include <chrono>
#include "CrossoverOperation.h"
using namespace std;

CrossoverOperation::CrossoverOperation() {
	seed = chrono::system_clock::now().time_since_epoch().count();
}

CrossoverOperation::CrossoverOperation(int newSeed, int newCrossoverRate) : seed(newSeed) {}
