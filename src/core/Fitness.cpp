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

Fitness::Fitness(std::vector<double> initial) {
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

void Fitness::add(std::vector<double> components) {
	for (auto component:components)
		this->add(component);
}

void Fitness::add(Fitness target) {
	this->add(target.getComponents());
}

double Fitness::collapse() const {
	return std::accumulate(
		this->components.begin(),
		this->components.end(),
		0.0
	);
}

std::vector<double> Fitness::getComponents() const {
	return this->components;
}

// It's generally a safe assumption that two Fitness objects will have the
// same "sources" of fitness, in the same order
// Therefore we operate on them mathematically, in order
// This preserves "relative" value - e.g. after subtraction the overall value
// will still be positive if the first operand is larger (has higher fitness)
Fitness Fitness::mathOperation(
	const Fitness& rhs,
	std::function<double(double, double)> op
) const {
	std::vector<double> lhsComponents = this->getComponents();
	std::vector<double> rhsComponents = rhs.getComponents();
	std::vector<double> components;

	// In case one gets more values than another - can happen with
	// apportionment
	unsigned int overallLen = std::max(
		lhsComponents.size(),
		rhsComponents.size()
	);

	for (unsigned int i = 0; i < overallLen; i++) {
		if (i < lhsComponents.size() and i < rhsComponents.size()) {
			components.push_back(
				op(lhsComponents[i], rhsComponents[i])
			);
		} else if (i < lhsComponents.size()) {
			components.push_back(lhsComponents[i]);
		} else if (i < rhsComponents.size()) {
			components.push_back(rhsComponents[i]);
		}
	}

	return Fitness(components);
}

Fitness Fitness::operator+(const Fitness& rhs) const {
	return this->mathOperation(rhs, std::plus<double>());
}

Fitness Fitness::operator-(const Fitness& rhs) const {
	return this->mathOperation(rhs, std::minus<double>());
}

bool Fitness::operator==(const Fitness& rhs) const {
	std::vector<double> rhsComponents = rhs.getComponents();
	if (rhsComponents.size() != this->components.size()) return false;
	for (unsigned int i = 0; i < this->components.size(); i++)
		if (rhsComponents[i] != this->components[i]) return false;

	return true;
}

bool Fitness::operator!=(const Fitness& rhs) const {
	return !(*this == rhs);
}

bool Fitness::operator>(const Fitness& rhs) const {
	return this->collapse() > rhs.collapse();
}

bool Fitness::operator<(const Fitness& rhs) const {
	return rhs > *this;
}

// TODO: Determine whether these implementations of >= and <= make the most
// sense
bool Fitness::operator>=(const Fitness& rhs) const {
	return !(*this < rhs);
}

bool Fitness::operator<=(const Fitness& rhs) const {
	return !(*this > rhs);
}

std::ostream& operator<<(std::ostream& os, const Fitness& fitness) {
	std::vector<double> components = fitness.getComponents();
	os << "{";
	for (unsigned int i = 0; i < components.size(); i++)
		os << components[i] << (i < components.size() - 1 ? ", " : "");
	os << "}";
	return os;
}
