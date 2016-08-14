#ifndef INSTRUMENTS_POPULATION_GenerationalCSVInstrument
#define INSTRUMENTS_POPULATION_GenerationalCSVInstrument

#include "CSVInstrument.hpp"

class GenerationalCSVInstrument: public CSVInstrument {
	private:

	protected:
	GenerationalCSVInstrument(PopulationNode* target, std::string outFile);

	virtual void report()=0;

	public:
	virtual void initialReport();
	virtual void runtimeReport();
	virtual void endReport();
};

#endif
