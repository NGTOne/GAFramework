#include <exception>
#pragma once

class NodeAlreadyExistsException : public std::exception {
	virtual const char * what() const throw();
};
