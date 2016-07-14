#include "exception/CoevConstructionException.hpp"

CoevConstructionException::CoevConstructionException() :
	CustomMessageException(
		"Unable to construct co-evolutionary system."
	) {}

CoevConstructionException::CoevConstructionException(
	std::string message
) : CustomMessageException(message) {}
