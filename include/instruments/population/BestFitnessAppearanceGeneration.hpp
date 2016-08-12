#ifndef INSTRUMENTS_POPULATION_BestFitnessAppearanceGeneration
#define INSTRUMENTS_POPULATION_BestFitnessAppearanceGeneration

#include "../../core/instruments/PopulationInstrument.hpp"

class BestFitnessAppearanceGeneration: public PopulationInstrument {
	private:
	class GenerationInfo {
		private:

		protected:
		unsigned int numAppearances;
		double bestFitness;

		public:
		GenerationInfo(unsigned int numAppearances, double bestFitness);
		unsigned int getAppearances();
		double getBest();
	};

	protected:
	unsigned int bestGeneration;
	unsigned int numAppearances;
	double bestFitness;

	GenerationInfo evaluateNode();

	public:
	BestFitnessAppearanceGeneration(
		PopulationNode* target,
		std::string outFile
	);

	void initialReport();
	void runtimeReport();
	void endReport();
};

#endif
