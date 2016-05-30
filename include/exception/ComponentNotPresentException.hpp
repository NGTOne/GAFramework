#include <exception>
#pragma once

class ComponentNotPresentException : public std::exception {
	virtual const char * what() const throw();
};
