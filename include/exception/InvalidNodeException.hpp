#include <exception>
#pragma once

class InvalidNodeException : public std::exception {
	virtual const char * what() const throw();
};
