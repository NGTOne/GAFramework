#include "core/Fitness.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <algorithm>
#include <vector>
#include <limits>

Fitness::Fitness() {
	this->components = {};
}

Fitness::Fitness(double initial, FitnessSource source) {
	this->components.push_back(std::make_tuple(initial, source));
}

Fitness::Fitness(std::initializer_list<FitnessPair> initial) {
	this->components.insert(
		this->components.end(),
		initial.begin(),
		initial.end()
	);
}

Fitness::Fitness(std::vector<FitnessPair> initial) {
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

void Fitness::add(double component, FitnessSource source) {
	this->add(std::make_tuple(component, source));
}

void Fitness::add(FitnessPair component) {
	this->components.push_back(component);
}

void Fitness::add(std::initializer_list<FitnessPair> components) {
	for (auto component: components)
		this->add(component);
}

void Fitness::add(std::vector<FitnessPair> components) {
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
		0.0,
		[] (double first, FitnessPair second) -> double {
			return first + std::get<0>(second);
		}
	);
}

std::vector<FitnessPair> Fitness::getComponents() const {
	return this->components;
}

// Yes, I KNOW it's O(n^2)
// It's not likely to be too big a deal here
std::vector<FitnessPair> Fitness::matchComponentsBySource(
	std::vector<FitnessPair> toMatch
) const {
	std::vector<FitnessPair> matched = toMatch;

	for (unsigned int i = 0; i < this->components.size(); i++) {
		FitnessSource lhs = std::get<1>(this->components[i]);
		for (unsigned int k = 0; k < matched.size(); k++) {
			FitnessSource rhs = std::get<1>(matched[k]);
			if (lhs == rhs) {
				FitnessPair temp = matched[i];
				matched[i] = matched[k];
				matched[k] = temp;
			}
		}
	}

	return matched;
}

Fitness Fitness::mathOperation(
	const Fitness& rhs,
	std::function<double(double, double)> op
) const {
	std::vector<FitnessPair> lhsComponents = this->getComponents();
	// This way, they're guaranteed to be in the same order
	std::vector<FitnessPair> rhsComponents =
		this->matchComponentsBySource(rhs.getComponents());
	std::vector<FitnessPair> newComponents;

	// In case one gets more values than another - can happen with
	// apportionment
	unsigned int overallLen = std::max(
		lhsComponents.size(),
		rhsComponents.size()
	);

	for (unsigned int i = 0; i < overallLen; i++) {
		if (i < lhsComponents.size() and i < rhsComponents.size()) {
			newComponents.push_back(std::make_tuple(
				op(
					std::get<0>(lhsComponents[i]),
					std::get<0>(rhsComponents[i])
				),
				std::get<1>(lhsComponents[i])
			));
		} else if (i < lhsComponents.size()) {
			newComponents.push_back(lhsComponents[i]);
		} else if (i < rhsComponents.size()) {
			newComponents.push_back(rhsComponents[i]);
		}
	}

	return Fitness(newComponents);
}

Fitness Fitness::operator+(const Fitness& rhs) const {
	return this->mathOperation(rhs, std::plus<double>());
}

Fitness Fitness::operator-(const Fitness& rhs) const {
	return this->mathOperation(rhs, std::minus<double>());
}

bool Fitness::operator==(const Fitness& rhs) const {
	std::vector<FitnessPair> rhsComponents = rhs.getComponents();
	if (rhsComponents.size() != this->components.size()) return false;

	rhsComponents = this->matchComponentsBySource(rhsComponents);
	for (unsigned int i = 0; i < this->components.size(); i++)
		if (std::get<0>(rhsComponents[i]) !=
			std::get<0>(this->components[i])) return false;

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

Fitness Fitness::lowestPossible() {
	return Fitness(
		std::numeric_limits<double>::lowest(),
		FitnessSource()
	);
}

std::ostream& operator<<(std::ostream& os, const Fitness& fitness) {
	std::vector<FitnessPair> components = fitness.getComponents();
	os << "{";
	for (unsigned int i = 0; i < components.size(); i++)
		os << std::get<0>(components[i])
			<< (i < components.size() - 1 ? ", " : "");
	os << "}";
	return os;
}
