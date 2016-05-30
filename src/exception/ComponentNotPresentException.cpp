#include "exception/ComponentNotPresentException.hpp"

const char * ComponentNotPresentException::what() const throw() {
	return "The specified component could not be found within this genome.";
}
