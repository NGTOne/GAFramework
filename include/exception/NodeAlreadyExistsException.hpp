#ifndef EXCEPTION_NodeAlreadyExistsException
#define EXCEPTION_NodeAlreadyExistsException

#include "CustomMessageException.hpp"

class NodeAlreadyExistsException : public CustomMessageException {
	public:
	NodeAlreadyExistsException();
	NodeAlreadyExistsException(std::string message);
};

#endif
