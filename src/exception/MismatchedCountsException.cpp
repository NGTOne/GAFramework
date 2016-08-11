#include "exception/MismatchedCountsException.hpp"

MismatchedCountsException::MismatchedCountsException() :
	CustomMessageException(
		"Two or more array/vector values passed to this function do not have the same number of elements."
	) {}

MismatchedCountsException::MismatchedCountsException(
	std::string message
) : CustomMessageException(message) {}
