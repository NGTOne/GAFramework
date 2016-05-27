#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "1maxFitness.hpp"

using namespace std;

OneMaxFitness::OneMaxFitness() : ObjectiveFunction() {}

int OneMaxFitness::checkFitness(Genome * genome) {
	int total = 0;
	Genome flattened = genome->flattenGenome();
	vector<int> flattenedGenome = flattened.getGenome();
	vector<Locus*> loci = flattened.getLoci();

	for (int i = 0; i < flattenedGenome.size(); i++)
		total += ((IntLocus*)loci[i])->getIndex(flattenedGenome[i]);

	return total;
}

string OneMaxToString::toString(Genome * genome) {
	stringstream ss;
	Genome flattened = genome->flattenGenome();
	vector<int> rawGenome = flattened.getGenome();
	vector<Locus*> loci = flattened.getLoci();
	
	for (int i = 0; i < rawGenome.size(); i++)
		ss << ((IntLocus*)loci[i])->getIndex(rawGenome[i]);
		
	return ss.str();
}
