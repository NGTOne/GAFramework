#include "exception/NoEvolutionOrderException.hpp"

NoEvolutionOrderException::NoEvolutionOrderException() :
	CustomMessageException(
		"No evolution order has been explicitly specified. Please specify an evolutionary order."
	) {}

NoEvolutionOrderException::NoEvolutionOrderException(
	std::string message
) : CustomMessageException(message) {}
