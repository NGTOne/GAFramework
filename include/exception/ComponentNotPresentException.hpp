#ifndef EXCEPTION_ComponentNotPresentException
#define EXCEPTION_ComponentNotPresentException

#include "CustomMessageException.hpp"

class ComponentNotPresentException : public CustomMessageException {
	public:
	ComponentNotPresentException();
	ComponentNotPresentException(std::string message);
};

#endif
