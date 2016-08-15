#ifndef EXCEPTION_CustomMessageException
#define EXCEPTION_CustomMessageException

#include <exception>
#include <string>

class CustomMessageException : public std::exception {
	private:
	std::string message;

	protected:

	public:
	explicit CustomMessageException(std::string message);
	virtual const char * what() const throw();
};

#endif
