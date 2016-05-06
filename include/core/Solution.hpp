#include <vector>
#include "Genome.hpp"
#include "PropertiesList.hpp"
#include "Locus.hpp"
//#include "ObjectiveFunction.hpp"
//#include "ToStringFunction.hpp"
#include <string>
#pragma once

class Solution {
	private:

	protected:
	Genome * genome;
	PropertiesList * properties;
	//ToStringFunction * toString;
	//std::vector<ObjectiveFunction*> objectives;

	void init(Genome * genome, PropertiesList * properties);

	public:
	Solution();
	Solution(Genome * genome);
	Solution(Solution * copyTarget, bool randomize);
	Solution(Solution * copyTarget, int rawGenes[]);
	Solution(Genome * genome, PropertiesList * properties);
	Solution(std::vector<Locus*> loci);
	~Solution();

	//int evaluateFitness();
	int getFitness();
	PropertiesList * getProperties();

	Genome * getGenome();

	//std::string toString();
};
