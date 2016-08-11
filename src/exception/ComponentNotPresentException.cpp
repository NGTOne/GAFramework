#include "exception/ComponentNotPresentException.hpp"

ComponentNotPresentException::ComponentNotPresentException() :
	CustomMessageException(
		"The specified component could not be found within this genome."
	) {}

ComponentNotPresentException::ComponentNotPresentException(
	std::string message
) : CustomMessageException(message) {}
