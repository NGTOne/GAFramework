//This is an abstract class for crossover operations. Lets us define any 
//crossover we like, and use it for a given Individual.

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "CrossoverOperation.h"
using namespace std;

CrossoverOperation::CrossoverOperation() {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(seed);
}

CrossoverOperation::CrossoverOperation(unsigned newSeed) : seed(newSeed) {
	init(newSeed);
}

void CrossoverOperation::init(unsigned newSeed) {
	mt19937 newGenerator(newSeed);
	generator = newGenerator;
}
