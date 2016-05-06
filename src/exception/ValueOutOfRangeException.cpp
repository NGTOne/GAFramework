#include "exception/ValueOutOfRangeException.hpp"

const char * ValueOutOfRangeException::what() const throw() {
	return "The value provided was out of range!";
}
