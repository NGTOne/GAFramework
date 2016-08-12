#include "core/utils/HierLogger.hpp"
#include <iostream>
#include <fstream>

std::map<std::string, std::ofstream&> HierLogger::streams;

bool HierLogger::alreadyOpen(std::string filename) {
	return HierLogger::streams.find(filename) != HierLogger::streams.end();
}

void HierLogger::open(std::string filename) {
	std::ofstream stream;
	stream.open(filename);
	if (!HierLogger::alreadyOpen(filename))
		HierLogger::streams.emplace(filename, stream);
}

void HierLogger::log(std::string message, std::string filename) {
	HierLogger::open(filename);
	std::ofstream& stream = HierLogger::streams.at(filename);
	stream << message;
}

void HierLogger::close(std::string filename) {
	if (HierLogger::alreadyOpen(filename)) {
		std::ofstream& stream = HierLogger::streams.at(filename);
		stream.close();
	}
}
