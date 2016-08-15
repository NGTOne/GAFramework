#ifndef EXCEPTION_MismatchedCountsException
#define EXCEPTION_MismatchedCountsException

#include "CustomMessageException.hpp"

class MismatchedCountsException : public CustomMessageException {
	public:
	MismatchedCountsException();
	MismatchedCountsException(std::string message);
};

#endif
