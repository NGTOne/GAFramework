#include "exception/ValueOutOfRangeException.hpp"

ValueOutOfRangeException::ValueOutOfRangeException() :
	CustomMessageException(
		"The value provided was out of range!"
	) {}

ValueOutOfRangeException::ValueOutOfRangeException(
	std::string message
) : CustomMessageException(message) {}
