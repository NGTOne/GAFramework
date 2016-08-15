#ifndef EXCEPTION_ValueOutOfRangeException
#define EXCEPTION_ValueOutOfRangeException

#include "CustomMessageException.hpp"

class ValueOutOfRangeException : public CustomMessageException {
	public:
	ValueOutOfRangeException();
	ValueOutOfRangeException(std::string message);
};

#endif
