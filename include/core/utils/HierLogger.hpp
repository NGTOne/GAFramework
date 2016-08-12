#ifndef CORE_UTILS_HierLogger
#define CORE_UTILS_HierLogger

#include "HierLoggerStream.hpp"
#include <map>

class HierLogger {
	private:
	static std::map<std::string, HierLoggerStream*> streams;

	static bool alreadyOpen(std::string filename);
	static void open(std::string filename);

	protected:

	public:
	static void log(std::string message, std::string filename);
	static void close(std::string filename);
};

#endif
