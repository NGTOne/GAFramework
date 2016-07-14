#include <exception>
#include <string>
#pragma once

class CustomMessageException : public std::exception {
	private:
	std::string message;

	protected:

	public:
	explicit CustomMessageException(std::string message);
	virtual const char * what() const throw();
};
