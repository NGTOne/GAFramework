#include <exception>
#pragma once

class ValueOutOfRangeException : public std::exception {
	virtual const char * what() const throw();
};
