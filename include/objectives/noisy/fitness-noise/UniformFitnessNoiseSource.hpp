#ifndef OBJECTIVES_NOISY_FITNESS_NOISE_UniformFitnessNoiseSource
#define OBJECTIVES_NOISY_FITNESS_NOISE_UniformFitnessNoiseSource

#include "FitnessNoiseSource.hpp"
#include "../../../core/utils/HierRNG.hpp"

template <typename T>
class UniformFitnessNoiseSource: public FitnessNoiseSource {
	private:

	protected:
	T low;
	T high;

	public:
	UniformFitnessNoiseSource(T low, T high);

	float addNoise(float cleanFitness);
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
float UniformFitnessNoiseSource<T>::addNoise(float cleanFitness) {
	return cleanFitness + HierRNG::uniform<T>(this->low, this->high);
}

#endif
