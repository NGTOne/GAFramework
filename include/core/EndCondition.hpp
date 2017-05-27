#ifndef CORE_EndCondition
#define CORE_EndCondition

#include "Genome.hpp"
#include "Fitness.hpp"
#include "EABehaviourObject.hpp"
#include <vector>

class EndCondition : public EABehaviourObject {
	private:

	protected:
	virtual bool checkSolution(Genome * target, Fitness targetFitness);
	
	public:
	EndCondition();
	virtual ~EndCondition();

	virtual bool checkCondition(
		std::vector<Genome*> genomes,
		std::vector<Fitness> fitnesses,
		unsigned int currentIteration
	)=0;
};

#endif
