#include <vector>
#include <random>
#include "../../../nodes/EANode/MutationOperation.hpp"
#include "../../../core/EABehaviourObject.hpp"
#pragma once

class GeneticNoiseSource : public EABehaviourObject {
	private:

	protected:
	MutationOperation * mutator;

	GeneticNoiseSource();
	GeneticNoiseSource(MutationOperation * mutator);

	public:
	~GeneticNoiseSource();
	virtual void registerInternalObjects();

	virtual Genome addNoise(Genome * target);
	Genome addNoise(Genome target);
};
