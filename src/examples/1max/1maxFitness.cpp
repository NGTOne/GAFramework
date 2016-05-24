#include <sstream>
#include "1maxFitness.hpp"
#include <libHierGA/HierGA.hpp>

using namespace std;

OneMaxFitness::OneMaxFitness() : ObjectiveFunction() {}

int OneMaxFitness::checkFitness(Genome * genome) {
	int total = 0;
	vector<int> rawGenome = genome->getGenome();
	vector<Locus*> loci = genome->getLoci();

	for (int i = 0; i < genome->genomeLength(); i++)
		total += ((IntLocus*)loci[i])->getIndex(rawGenome[i]);

	return total;
}

string OneMaxToString::toString(Genome * genome) {
	stringstream ss;
	vector<int> rawGenome = genome->getGenome();
	vector<Locus*> loci = genome->getLoci();
	
	for (int i = 0; i < genome->genomeLength(); i++)
		ss << ((IntLocus*)loci[i])->getIndex(rawGenome[i]);
		
	return ss.str();
}
