#include "exception/CustomMessageException.hpp"

CustomMessageException::CustomMessageException(std::string message) {
	this->message = message;
}

const char * CustomMessageException::what() const throw() {
	return this->message.c_str();
}
