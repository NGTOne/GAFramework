#ifndef EXCEPTION_CoevConstructionException
#define EXCEPTION_CoevConstructionException

#include "CustomMessageException.hpp"

class CoevConstructionException : public CustomMessageException {
	public:
	CoevConstructionException();
	CoevConstructionException(std::string message);
};

#endif
