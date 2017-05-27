#ifndef OBJECTIVES_NOISY_FITNESS_NOISE_UniformFitnessNoiseSource
#define OBJECTIVES_NOISY_FITNESS_NOISE_UniformFitnessNoiseSource

#include "objectives/noisy/fitness-noise/FitnessNoiseSource.hpp"
#include "core/utils/HierRNG.hpp"

template <typename T>
class UniformFitnessNoiseSource: public FitnessNoiseSource {
	private:

	protected:
	T low;
	T high;

	public:
	UniformFitnessNoiseSource(T low, T high);
	Fitness addNoise(Fitness cleanFitness);
};

template <typename T>
UniformFitnessNoiseSource<T>::UniformFitnessNoiseSource(
	T low,
	T high
) : FitnessNoiseSource() {
	this->low = low;
	this->high = high;
}

template <typename T>
Fitness UniformFitnessNoiseSource<T>::addNoise(Fitness cleanFitness) {
	return this->noisify(cleanFitness, [this](double component) -> double {
		return component + HierRNG::uniform<T>(this->low, this->high);
	});
}

#endif
