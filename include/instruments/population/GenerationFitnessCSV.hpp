#ifndef INSTRUMENTS_POPULATION_GenerationFitnessCSV
#define INSTRUMENTS_POPULATION_GenerationFitnessCSV

#include "GenerationalCSVInstrument.hpp"
#include <vector>
#include <map>

class GenerationFitnessCSV: public GenerationalCSVInstrument {
	private:

	protected:
	std::vector<double> buckets;
	double resolution;

	double bucket(Fitness actual);
	void report();

	public:
	GenerationFitnessCSV(
		PopulationNode* target,
		std::string outFile,
		double bottomFitness,
		double topFitness,
		double resolution = 1
	);
};

#endif
