#pragma once
#include "../../../../core/Genome.hpp"
#include "../../../../core/EABehaviourObject.hpp"
#include <vector>

class NichingStrategy : public EABehaviourObject {
	private:

	protected:

	public:
	virtual ~NichingStrategy();
	virtual void registerInternalObjects(NodeGarbageCollector & collector);

	virtual std::vector<unsigned int> getIndices(
		std::vector<Genome*> initialPopulation,
		std::vector<Genome*> newPopulation
	)=0;
};
