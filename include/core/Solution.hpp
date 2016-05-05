#include <vector>
#include "Genome.hpp"
#include "PropertiesList.hpp"
#include "Locus.hpp"
#include <string>
#pragma once

class Solution {
	private:

	protected:
	Genome * genome;
	PropertiesList * properties;

	public:
	Solution();
	Solution(Genome * newGenome);
	Solution(Solution * copyTarget, bool randomize);
	Solution(Solution * copyTarget, int newGenome[]);
	Solution(Genome * newGenome, PropertiesList * newProperties);
	Solution(std::vector<Locus*> loci);
	~Solution();

	int evaluateFitness();
	int getFitness();
	PropertiesList * getProperties();

	Genome * getGenome();

	std::string toString();
};
