#include <exception>
#pragma once

class NoEvolutionOrderException : public exception {
	virtual const char * what() const throw();
};
