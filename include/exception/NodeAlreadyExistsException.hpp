#include <exception>
#pragma once

class NodeAlreadyExistsException : public exception {
	virtual const char * what() const throw();
};
