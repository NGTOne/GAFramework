#ifndef INSTRUMENTS_POPULATION_GenerationFitnessCSV
#define INSTRUMENTS_POPULATION_GenerationFitnessCSV

#include "GenerationalCSVInstrument.hpp"
#include <vector>
#include <map>

class GenerationFitnessCSV: public GenerationalCSVInstrument {
	private:

	protected:
	std::vector<float> buckets;
	float resolution;

	float bucket(float actual);
	void report();

	public:
	GenerationFitnessCSV(
		PopulationNode* target,
		std::string outFile,
		float bottomFitness,
		float topFitness,
		float resolution = 1
	);
};

#endif
