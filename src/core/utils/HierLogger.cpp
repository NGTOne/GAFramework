#include "core/utils/HierLogger.hpp"
#include <iostream>
#include <fstream>

std::map<std::string, HierLoggerStream*> HierLogger::streams;

bool HierLogger::alreadyOpen(std::string filename) {
	return HierLogger::streams.find(filename) != HierLogger::streams.end();
}

void HierLogger::open(std::string filename) {
	if (!HierLogger::alreadyOpen(filename))
		HierLogger::streams.emplace(
			filename,
			new HierLoggerStream(filename)
		);
}

void HierLogger::log(std::string message, std::string filename) {
	HierLogger::open(filename);
	HierLogger::streams.at(filename)->write(message);
}

void HierLogger::close(std::string filename) {
	if (HierLogger::alreadyOpen(filename)) {
		delete(HierLogger::streams.at(filename));
		HierLogger::streams.erase(filename);
	}
}
