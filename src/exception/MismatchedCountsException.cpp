#include "exception/MismatchedCountsException.hpp"

const char * MismatchedCountsException::what() const throw() {
	return "Two or more array/vector values passed to this function do not have the same number of elements.";
}
