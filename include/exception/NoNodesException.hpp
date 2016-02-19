#include <exception>
#pragma once

class NoNodesException : public exception {
	virtual const char * what() const throw();
};
