#include "core/Fitness.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <algorithm>
#include <vector>

Fitness::Fitness() {
	this->components = {};
}

Fitness::Fitness(double initial) {
	this->components.push_back(initial);
}

Fitness::Fitness(std::initializer_list<double> initial) {
	this->components.insert(
		this->components.end(),
		initial.begin(),
		initial.end()
	);
}

void Fitness::drop() {
	this->drop(this->components.size() - 1);
}

void Fitness::drop(unsigned int index) {
	this->components.erase(this->components.begin() + index);
}

void Fitness::drop(unsigned int start, unsigned int end) {
	if (start < end) throw ValueOutOfRangeException("Start value is greater than end value!");
	auto begin = this->components.begin();
	this->components.erase(begin + start, begin + end);
}

void Fitness::drop(std::initializer_list<unsigned int> indices) {
	std::vector<unsigned int> sortedIndices = indices;
	std::sort(
		sortedIndices.begin(),
		sortedIndices.end(),
		std::greater<unsigned int>()
	);

	for (auto index: sortedIndices)
		this->components.erase(this->components.begin() + index);
}

void Fitness::add(double component) {
	this->components.push_back(component);
}

void Fitness::add(std::initializer_list<double> components) {
	for (auto component: components)
		this->add(component);
}

double Fitness::collapse() {
	return std::accumulate(
		this->components.begin(),
		this->components.end(),
		0.0
	);
}

std::vector<double> Fitness::getComponents() {
	return this->components;
}
