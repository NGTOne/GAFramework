#ifndef CORE_INSTRUMENTS_GlobalInstrument
#define CORE_INSTRUMENTS_GlobalInstrument

#include "HierInstrument.hpp"
#include "../HierarchicalEA.hpp"

class GlobalInstrument: public HierInstrument {
	private:

	protected:
	HierarchicalEA* target;

	public:
	GlobalInstrument(HierarchicalEA* target, std::string outFile);
	virtual void initialReport()=0;
	virtual void runtimeReport()=0;
	virtual void endReport()=0;
};

#endif
