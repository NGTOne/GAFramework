#ifndef CORE_EndCondition
#define CORE_EndCondition

#include "Genome.hpp"
#include "EABehaviourObject.hpp"
#include <vector>

class EndCondition : public EABehaviourObject {
	private:

	protected:
	virtual bool checkSolution(Genome * target, float targetFitness);
	
	public:
	EndCondition();
	virtual ~EndCondition();
	virtual void registerInternalObjects(NodeGarbageCollector & collector);

	virtual bool checkCondition(
		std::vector<Genome*> genomes,
		std::vector<float> fitnesses,
		unsigned int currentIteration
	)=0;
};

#endif
