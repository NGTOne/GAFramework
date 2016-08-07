#include "../core/Locus.hpp"
#include "../core/PopulationNode.hpp"
#include <vector>
#include <string>
#pragma once

class PopulationLocus: public Locus {
	private:

	protected:
	PopulationNode* node;

	public:
	PopulationLocus(PopulationNode* node);
	~PopulationLocus();

	Gene* getGene();
	Gene* getGene(double index);

	double randomIndex();
	double topIndex();
	double bottomIndex();
	double closestIndex(double index);
	bool outOfRange(double index);

	bool isConstructive();
	virtual bool isFake();

	bool usesSpecies(Genome* target);

	virtual std::string toString();
	virtual std::string nodeName();
	virtual std::string flatten(Gene* index);

	virtual boost::any getIndex(Gene* index);
	PopulationNode* getNode();
};
