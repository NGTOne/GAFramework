#include "exception/InvalidBlanketException.hpp"

InvalidBlanketException::InvalidBlanketException() :
	CustomMessageException(
		"Invalid blanket specified. Ensure that the specified blanket is a complete hierarchy (i.e. can be resolved to a flat genome) and has only one root node."
	) {}

InvalidBlanketException::InvalidBlanketException(
	std::string message
) : CustomMessageException(message) {}
