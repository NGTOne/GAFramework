#include <exception>
#pragma once

class InvalidNodeException : public exception {
	virtual const char * what() const throw();
};
