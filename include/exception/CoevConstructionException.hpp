#include "CustomMessageException.hpp"
#pragma once

class CoevConstructionException : public CustomMessageException {
	public:
	CoevConstructionException();
	CoevConstructionException(std::string message);
};
