#ifndef CORE_INSTRUMENTS_PopulationInstrument
#define CORE_INSTRUMENTS_PopulationInstrument

#include "HierInstrument.hpp"
#include "../PopulationNode.hpp"

class PopulationInstrument: public HierInstrument {
	private:

	protected:
	PopulationNode* target;

	public:
	PopulationInstrument(PopulationNode* target, std::string outFile);
	virtual void initialReport()=0;
	virtual void runtimeReport()=0;
	virtual void endReport()=0;
};

#endif
