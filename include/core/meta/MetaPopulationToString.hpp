#include "../ToStringFunction.hpp"

class MetaPopulationToString : public ToStringFunction {
	private:

	protected:
	ToStringFunction * flattenedToString;

	public:
	MetaPopulationToString(ToStringFunction * flattenedToString);
	std::string toString(Genome * genome);
};
