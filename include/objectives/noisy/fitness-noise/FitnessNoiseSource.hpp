#ifndef OBJECTIVES_NOISY_FITNESS_NOISE_FitnessNoiseSource
#define OBJECTIVES_NOISY_FITNESS_NOISE_FitnessNoiseSource

#include "core/EABehaviourObject.hpp"
#include "core/Fitness.hpp"
#include <functional>

class FitnessNoiseSource : public EABehaviourObject {
	private:

	protected:
	FitnessNoiseSource();
	Fitness noisify(
		Fitness cleanFitness,
		std::function<double(double)> noisemaker
	);

	public:
	virtual Fitness addNoise(Fitness cleanFitness)=0;
};

#endif
