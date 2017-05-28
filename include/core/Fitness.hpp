#ifndef CORE_Fitness
#define CORE_Fitness

#include <vector>
#include <initializer_list>
#include <ostream>
#include <functional>
#include <tuple>

#include "FitnessSource.hpp"

class FitnessSource;
typedef std::tuple<double, FitnessSource> FitnessPair;

class Fitness {
	private:
	Fitness mathOperation(
		const Fitness& rhs,
		std::function<double(double, double)> op
	) const;

	std::vector<FitnessPair> matchComponentsBySource(
		std::vector<FitnessPair> toMatch
	) const;

	protected:
	std::vector<FitnessPair> components;

	public:
	Fitness();
	Fitness(double initial, FitnessSource source);
	Fitness(std::initializer_list<FitnessPair> initial);
	Fitness(std::vector<FitnessPair> initial);

	void drop();
	void drop(unsigned int index);
	void drop(unsigned int start, unsigned int end);
	void drop(std::initializer_list<unsigned int> indices);

	void add(double component, FitnessSource source);
	void add(std::tuple<double, FitnessSource> component);
	void add(std::initializer_list<FitnessPair> components);
	void add(std::vector<FitnessPair> components);
	void add(Fitness target);

	// Obviously there's lots of possible different ways to do this
	// We'll default to just summing up the components
	virtual double collapse() const;
	std::vector<FitnessPair> getComponents() const;

	virtual Fitness operator+(const Fitness& rhs) const;
	virtual Fitness operator-(const Fitness& rhs) const;

	virtual bool operator==(const Fitness& rhs) const;
	virtual bool operator!=(const Fitness& rhs) const;
	virtual bool operator>(const Fitness& rhs) const;
	virtual bool operator<(const Fitness& rhs) const;
	virtual bool operator>=(const Fitness& rhs) const;
	virtual bool operator<=(const Fitness& rhs) const;

	static Fitness lowestPossible();
};

std::ostream& operator<<(std::ostream& os, const Fitness& fitness);

#endif
