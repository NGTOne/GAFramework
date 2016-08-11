#include "CustomMessageException.hpp"
#pragma once

class ValueOutOfRangeException : public CustomMessageException {
	public:
	ValueOutOfRangeException();
	ValueOutOfRangeException(std::string message);
};
