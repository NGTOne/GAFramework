#ifndef EXCEPTION_NoEvolutionOrderException
#define EXCEPTION_NoEvolutionOrderException

#include "CustomMessageException.hpp"

class NoEvolutionOrderException : public CustomMessageException {
	public:
	NoEvolutionOrderException();
	NoEvolutionOrderException(std::string message);
};

#endif
