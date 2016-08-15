#ifndef NODES_EANODE_SYSTEMS_NICHING_NichingStrategy
#define NODES_EANODE_SYSTEMS_NICHING_NichingStrategy

#include "../../../../core/Genome.hpp"
#include "../../../../core/EABehaviourObject.hpp"
#include <vector>

class NichingStrategy : public EABehaviourObject {
	private:

	protected:

	public:
	virtual ~NichingStrategy();

	virtual std::vector<unsigned int> getIndices(
		std::vector<Genome*> initialPopulation,
		std::vector<Genome*> newPopulation
	)=0;
};

#endif
