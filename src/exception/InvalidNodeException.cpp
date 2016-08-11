#include "exception/InvalidNodeException.hpp"

InvalidNodeException::InvalidNodeException() :
	CustomMessageException(
		"This node does not exist! Try creating it before using it."
	) {}

InvalidNodeException::InvalidNodeException(
	std::string message
) : CustomMessageException(message) {}
