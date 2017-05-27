#include "core/Fitness.hpp"

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
