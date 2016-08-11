#include "CustomMessageException.hpp"
#pragma once

class InvalidBlanketException : public CustomMessageException {
	public:
	InvalidBlanketException();
	InvalidBlanketException(std::string message);
};
