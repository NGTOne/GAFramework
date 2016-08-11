#include "CustomMessageException.hpp"
#pragma once

class MismatchedCountsException : public CustomMessageException {
	public:
	MismatchedCountsException();
	MismatchedCountsException(std::string message);
};
