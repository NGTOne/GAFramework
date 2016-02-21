#include "exception/NodeAlreadyExistsException.hpp"

const char * NodeAlreadyExistsException::what() const throw() {
	return "A node with this name already exists.";
}
