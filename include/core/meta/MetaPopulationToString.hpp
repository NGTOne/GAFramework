#include "../ToStringFunction.hpp"
#include <vector>
#pragma once

class MetaPopulationToString : public ToStringFunction {
	private:

	protected:
	ToStringFunction * flattenedToString;

	public:
	MetaPopulationToString(ToStringFunction * flattenedToString);
	std::string toString(Genome * genome);
	bool isNested();
	std::vector<ToStringFunction*> getNested();
};
