#ifndef EXCEPTION_NoNodesException
#define EXCEPTION_NoNodesException

#include "CustomMessageException.hpp"

class NoNodesException : public CustomMessageException {
	public:
	NoNodesException();
	NoNodesException(std::string message);
};

#endif
