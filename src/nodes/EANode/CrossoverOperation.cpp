//This is an abstract class for crossover operations. Lets us define any 
//crossover we like, and use it for a given Individual.

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "nodes/EANode/CrossoverOperation.hpp"
using namespace std;

CrossoverOperation::CrossoverOperation() {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(seed);
}

CrossoverOperation::CrossoverOperation(unsigned seed) : seed(seed) {
	init(seed);
}

void CrossoverOperation::init(unsigned seed) {
	mt19937 newGenerator(seed);
	generator = newGenerator;
}
