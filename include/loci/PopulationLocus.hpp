#include "../core/Locus.hpp"
#include "../core/PopulationNode.hpp"
#include <vector>
#include <string>
#pragma once

class PopulationLocus: public Locus {
	private:

	protected:
	PopulationNode * node;

	public:
	PopulationLocus(PopulationNode * node);
	~PopulationLocus();

	virtual Genome * getIndex(unsigned int index);
	virtual unsigned int topIndex();
	virtual bool outOfRange(unsigned int i);
	bool isConstructive();
	virtual bool isFake();
	bool usesSpecies(Genome * target);

	virtual std::string toString();
	virtual std::string nodeName();
	virtual std::string flatten(unsigned int index);
	PopulationNode * getNode();
};
