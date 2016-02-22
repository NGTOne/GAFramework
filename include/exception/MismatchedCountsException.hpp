#include <exception>
#pragma once

class MismatchedCountsException : public std::exception {
	virtual const char * what() const throw();
};
