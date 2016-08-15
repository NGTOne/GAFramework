#ifndef EXCEPTION_InvalidBlanketException
#define EXCEPTION_InvalidBlanketException

#include "CustomMessageException.hpp"

class InvalidBlanketException : public CustomMessageException {
	public:
	InvalidBlanketException();
	InvalidBlanketException(std::string message);
};

#endif
