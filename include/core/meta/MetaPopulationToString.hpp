#include "../ToStringFunction.hpp"
#include <vector>
#pragma once

class MetaPopulationToString : public ToStringFunction {
	private:

	protected:
	ToStringFunction * flattenedToString;

	public:
	MetaPopulationToString(ToStringFunction * flattenedToString);
	virtual void registerInternalObjects(NodeGarbageCollector & collector);
	std::string toString(Genome * genome);
	bool isNested();
	std::vector<ToStringFunction*> getNested();
};
