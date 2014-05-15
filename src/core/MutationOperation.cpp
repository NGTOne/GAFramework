//Abstract class for mutation operators. Lets us define any mutation operation we like.

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "MutationOperation.hpp"

using namespace std;

MutationOperation::MutationOperation() {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(0, seed);
}

MutationOperation::MutationOperation(double newMutationRate) {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(newMutationRate, seed);
}

MutationOperation::MutationOperation(double newMutationRate, unsigned newSeed) {
	init(newMutationRate, newSeed);
}

void MutationOperation::init(double newMutationRate, unsigned newSeed) {
	mutationRate = newMutationRate;
	seed = newSeed;
	mt19937 newGenerator(seed);
	generator = newGenerator;
}

string MutationOperation::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Random seed: " << seed << "\nMutation rate: " << mutationRate << "\n";

	returnString = ss.str();

	return returnString;

}
