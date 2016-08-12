#ifndef CORE_INSTRUMENTS_InstrumentCollection
#define CORE_INSTRUMENTS_InstrumentCollection

#include "HierInstrument.hpp"

class InstrumentCollection {
	private:

	protected:
	std::vector<HierInstrument*> instruments;

	public:
	~InstrumentCollection();
	void add(HierInstrument* instrument);
	void add(std::vector<HierInstrument*> instruments);

	void runInitial();
	void runRuntime();
	void runEnd();
};

#endif
