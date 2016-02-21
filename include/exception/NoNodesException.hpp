#include <exception>
#pragma once

class NoNodesException : public std::exception {
	virtual const char * what() const throw();
};
