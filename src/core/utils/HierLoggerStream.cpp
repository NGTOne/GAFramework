#include "core/utils/HierLoggerStream.hpp"
#include <fstream>

HierLoggerStream::HierLoggerStream(std::string filename) {
	this->stream.open(filename);
}

HierLoggerStream::~HierLoggerStream() {
	this->stream.close();
}

void HierLoggerStream::write(std::string message) {
	this->stream << message;
}
