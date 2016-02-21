#include "exception/NoEvolutionOrderException.hpp"

const char * NoEvolutionOrderException::what() const throw() {
	return "No evolution order has been explicitly specified. Please specify an evolutionary order.";
}
