#ifndef CORE_EVAL_HierarchicalToString
#define CORE_EVAL_HierarchicalToString

#include <string>
#include "../Genome.hpp"
#include "ToStringFunction.hpp"

class HierarchicalToString : public ToStringFunction {
	private:

	public:
	enum mode {flatten, printPlaceholders, omitPlaceholders};

	HierarchicalToString(mode printMode);
	virtual ~HierarchicalToString();
	std::string toString(Genome* genome);
	virtual std::string stringifySegment(std::vector<Gene*> genes)=0;

	bool isHierarchical();
	mode getPrintMode();

	protected:
	mode printMode;
};

#endif
