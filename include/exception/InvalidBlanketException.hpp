#include <exception>
#pragma once

class InvalidBlanketException : public std::exception {
	virtual const char * what() const throw();
};
