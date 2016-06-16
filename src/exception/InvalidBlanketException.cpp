#include "exception/InvalidBlanketException.hpp"

const char * InvalidBlanketException::what() const throw() {
	return "Invalid blanket specified. Ensure that the specified blanket is a complete hierarchy (i.e. can be resolved to a flat genome) and has only one root node.";
}
