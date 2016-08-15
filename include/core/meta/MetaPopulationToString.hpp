#ifndef CORE_META_MetaPopulationToString
#define CORE_META_MetaPopulationToString

#include "../eval/ToStringFunction.hpp"
#include <vector>

class MetaPopulationToString : public ToStringFunction {
	private:

	protected:
	ToStringFunction * flattenedToString;

	public:
	MetaPopulationToString(ToStringFunction * flattenedToString);
	virtual void registerInternalObjects();
	std::string toString(Genome * genome);
	bool isNested();
	std::vector<ToStringFunction*> getNested();
};

#endif
