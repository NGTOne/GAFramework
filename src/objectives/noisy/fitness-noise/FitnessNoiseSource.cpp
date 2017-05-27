#include "objectives/noisy/fitness-noise/FitnessNoiseSource.hpp"
#include <vector>

FitnessNoiseSource::FitnessNoiseSource() {}

Fitness FitnessNoiseSource::noisify(
	Fitness cleanFitness,
	std::function<double(double)> noisemaker
) {
	std::vector<double> components = cleanFitness.getComponents();
	for (unsigned int i = 0; i < components.size(); i++)
		components[i] = noisemaker(components[i]);
	return Fitness(components);
}
