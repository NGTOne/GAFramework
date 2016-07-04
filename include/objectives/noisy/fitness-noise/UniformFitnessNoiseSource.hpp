#include "FitnessNoiseSource.hpp"
#pragma once

template <typename T>
class UniformFitnessNoiseSource: public FitnessNoiseSource {
	private:

	protected:
	// A little bit'o'WTF here, but we need to be able to deal with all
	// different types of values
	using autoDist = typename std::conditional<
			std::is_integral<T>::value,
			std::uniform_int_distribution<T>,
			typename std::conditional<
				std::is_floating_point<T>::value,
				std::uniform_real_distribution<T>,
				void
			>::type
		>::type;

	autoDist modifierDist;

	public:
	UniformFitnessNoiseSource(T low, T high);
	UniformFitnessNoiseSource(T low, T high, unsigned int seed);

	float addNoise(float cleanFitness);
};

template <typename T>
UniformFitnessNoiseSource<T>::UniformFitnessNoiseSource(
	T low,
	T high
) : FitnessNoiseSource() {
	this->modifierDist = autoDist(low, high);
}

template <typename T>
UniformFitnessNoiseSource<T>::UniformFitnessNoiseSource(
	T low,
	T high,
	unsigned int seed
) : FitnessNoiseSource(seed) {
	this->modifierDist = autoDist(low, high);
}

template <typename T>
float UniformFitnessNoiseSource<T>::addNoise(float cleanFitness) {
	return cleanFitness + this->modifierDist(this->generator);
}
