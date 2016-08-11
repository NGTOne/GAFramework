#include "exception/NodeAlreadyExistsException.hpp"

NodeAlreadyExistsException::NodeAlreadyExistsException() :
	CustomMessageException(
		"A node with this name already exists."
	) {}

NodeAlreadyExistsException::NodeAlreadyExistsException(
	std::string message
) : CustomMessageException(message) {}
