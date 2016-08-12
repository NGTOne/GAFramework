#ifndef CORE_INSTRUMENTS_HierInstrument
#define CORE_INSTRUMENTS_HierInstrument

#include "../PopulationNode.hpp"

class HierInstrument {
	private:

	protected:
	std::string outFile;

	HierInstrument(std::string outFile);
	void write(std::string message);

	public:
	virtual void initialReport()=0;
	virtual void runtimeReport()=0;
	virtual void endReport()=0;
};

#endif
