#ifndef INSTRUMENTS_RunTimeTracker
#define INSTRUMENTS_RunTimeTracker

#include "../../core/instruments/GlobalInstrument.hpp"
#include <chrono>

class RunTimeTracker: public GlobalInstrument {
	private:

	protected:
	bool tracking;
	std::chrono::high_resolution_clock::time_point startTime;

	public:
	RunTimeTracker(HierarchicalEA* target, std::string outFile);

	void initialReport();
	void runtimeReport();
	void endReport();
};

#endif
