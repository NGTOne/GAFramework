#include "exception/NoNodesException.hpp"

const char * NoNodesException::what() const throw() {
	return "This hierarchical EA does not contain any population nodes or other optimizers. Please add some.";
}
