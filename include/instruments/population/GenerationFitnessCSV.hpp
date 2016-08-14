#ifndef INSTRUMENTS_POPULATION_GenerationFitnessCSV
#define INSTRUMENTS_POPULATION_GenerationFitnessCSV

#include "CSVInstrument.hpp"
#include <vector>
#include <map>

class GenerationFitnessCSV: public CSVInstrument {
	private:

	protected:
	std::vector<float> buckets;
	float resolution;

	float bucket(float actual);

	void reportFitnesses();

	public:
	GenerationFitnessCSV(
		PopulationNode* target,
		std::string outFile,
		float bottomFitness,
		float topFitness,
		float resolution = 1
	);

	void initialReport();
	void runtimeReport();
	void endReport();
};

#endif
