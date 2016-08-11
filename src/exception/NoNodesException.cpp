#include "exception/NoNodesException.hpp"

NoNodesException::NoNodesException() :
	CustomMessageException(
		"This hierarchical EA does not contain any population nodes or other optimizers. Please add some."
	) {}

NoNodesException::NoNodesException(
	std::string message
) : CustomMessageException(message) {}
