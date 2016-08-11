#include "CustomMessageException.hpp"
#pragma once

class InvalidNodeException : public CustomMessageException {
	public:
	InvalidNodeException();
	InvalidNodeException(std::string message);
};
