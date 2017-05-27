#ifndef INSTRUMENTS_POPULATION_TargetReachedGeneration
#define INSTRUMENTS_POPULATION_TargetReachedGeneration

#include "CSVInstrument.hpp"

class TargetReachedGeneration: public CSVInstrument {
	private:
	class GenerationInfo {
		private:

		protected:
		unsigned int numAppearances;
		Fitness bestFitness;

		public:
		GenerationInfo(
			unsigned int numAppearances,
			Fitness bestFitness
		);
		unsigned int getAppearances();
		Fitness getBest();
	};

	protected:
	unsigned int bestGeneration;
	unsigned int numAppearances;
	Fitness bestFitness;

	double targetFitness;
	double epsilon;
	unsigned int targetReachedGeneration;
	bool targetReached;

	GenerationInfo evaluateNode();
	void checkTargetReached(GenerationInfo info);

	public:
	TargetReachedGeneration(
		PopulationNode* target,
		std::string outFile,
		double targetFitness,
		double epsilon = 0
	);

	void initialReport();
	void runtimeReport();
	void endReport();
};

#endif
