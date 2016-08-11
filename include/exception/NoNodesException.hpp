#include "CustomMessageException.hpp"
#pragma once

class NoNodesException : public CustomMessageException {
	public:
	NoNodesException();
	NoNodesException(std::string message);
};
