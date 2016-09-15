#ifndef CORE_EVAL_HierarchicalToString
#define CORE_EVAL_HierarchicalToString

#include <string>
#include "../Genome.hpp"
#include "ToStringFunction.hpp"

class HierarchicalToString : public ToStringFunction {
	private:

	protected:
	bool printPlaceholders;

	public:
	HierarchicalToString(bool printPlaceholders);
	virtual ~HierarchicalToString();
	std::string toString(Genome* genome);
	virtual std::string stringifySegment(std::vector<Gene*> genes)=0;
};

#endif
