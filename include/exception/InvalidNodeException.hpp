#ifndef EXCEPTION_InvalidNodeException
#define EXCEPTION_InvalidNodeException

#include "CustomMessageException.hpp"

class InvalidNodeException : public CustomMessageException {
	public:
	InvalidNodeException();
	InvalidNodeException(std::string message);
};

#endif
