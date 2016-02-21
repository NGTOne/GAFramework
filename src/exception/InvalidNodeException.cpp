#include "exception/InvalidNodeException.hpp"

const char * InvalidNodeException::what() const throw() {
	return "This node does not exist! Try creating it before using it.";
}
