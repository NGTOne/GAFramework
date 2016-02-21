#include <exception>
#pragma once

class NoEvolutionOrderException : public std::exception {
	virtual const char * what() const throw();
};
