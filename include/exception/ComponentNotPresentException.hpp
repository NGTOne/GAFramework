#include "CustomMessageException.hpp"
#pragma once

class ComponentNotPresentException : public CustomMessageException {
	public:
	ComponentNotPresentException();
	ComponentNotPresentException(std::string message);
};
