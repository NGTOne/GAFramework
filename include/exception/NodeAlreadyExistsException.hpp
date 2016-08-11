#include "CustomMessageException.hpp"
#pragma once

class NodeAlreadyExistsException : public CustomMessageException {
	public:
	NodeAlreadyExistsException();
	NodeAlreadyExistsException(std::string message);
};
