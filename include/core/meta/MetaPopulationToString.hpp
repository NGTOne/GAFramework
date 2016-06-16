#include "../ToStringFunction.hpp"
#include "MetaPopulationFunction.hpp"

class MetaPopulationToString :
	public ToStringFunction,
	public MetaPopulationFunction
{
	private:

	protected:
	ToStringFunction * flattenedToString;

	public:
	MetaPopulationToString(ToStringFunction * flattenedToString);
	std::string toString(Genome * genome);
};
