#ifndef CORE_UTILS_HierLoggerStream
#define CORE_UTILS_HierLoggerStream

#include <fstream>

class HierLoggerStream {
	private:
	std::ofstream stream;

	protected:

	public:
	HierLoggerStream(std::string filename);
	~HierLoggerStream();
	void write(std::string message);
};

#endif
