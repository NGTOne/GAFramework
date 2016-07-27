#pragma once
#include "../../core/Genome.hpp"
#include "../../core/GenomeTemplate.hpp"
#include "../../core/EABehaviourObject.hpp"
#include <random>
#include <string>

/*
* This abstract class allows the creation of any mutation operator that is
* desired.
*/

class MutationOperation : public EABehaviourObject {
	private:

	protected:
        double mutationRate;

	virtual unsigned int getNewLocusValue(
		unsigned int currentValue,
		unsigned int largestPossibleValue
	)=0;
	unsigned int getNewLocusValue(
		std::tuple<unsigned int, Locus*> existing
	);

	void init(double mutationRate);

	public:
	MutationOperation();
	MutationOperation(double mutationRate);
	virtual ~MutationOperation();
	virtual void registerInternalObjects(NodeGarbageCollector & collector);

	virtual Genome * mutate(Genome * initialGenome);
	GenomeTemplate mutate(GenomeTemplate initial);

	std::string toString();
};
