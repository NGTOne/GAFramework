#include "CustomMessageException.hpp"
#pragma once

class NoEvolutionOrderException : public CustomMessageException {
	public:
	NoEvolutionOrderException();
	NoEvolutionOrderException(std::string message);
};
