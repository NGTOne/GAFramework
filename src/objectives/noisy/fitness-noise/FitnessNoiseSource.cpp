#include "objectives/noisy/fitness-noise/FitnessNoiseSource.hpp"
#include <vector>

FitnessNoiseSource::FitnessNoiseSource() {}

Fitness FitnessNoiseSource::noisify(
	Fitness cleanFitness,
	std::function<double(double)> noisemaker
) {
	std::vector<FitnessPair> components = cleanFitness.getComponents();
	for (unsigned int i = 0; i < components.size(); i++)
		components[i] = std::make_tuple(
			noisemaker(std::get<0>(components[i])),
			std::get<1>(components[i])
		);
	return Fitness(components);
}
