#ifndef CORE_Fitness
#define CORE_Fitness

#include <vector>
#include <initializer_list>
#include <ostream>

class Fitness {
	private:

	protected:
	std::vector<double> components;

	public:
	Fitness();
	Fitness(double initial);
	Fitness(std::initializer_list<double> initial);
	Fitness(std::vector<double> initial);

	void drop();
	void drop(unsigned int index);
	void drop(unsigned int start, unsigned int end);
	void drop(std::initializer_list<unsigned int> indices);

	void add(double component);
	void add(std::initializer_list<double> components);
	void add(std::vector<double> components);
	void add(Fitness target);

	// Obviously there's lots of possible different ways to do this
	// We'll default to just summing up the components
	virtual double collapse() const;
	std::vector<double> getComponents() const;

	virtual bool operator==(const Fitness& rhs) const;
	virtual bool operator!=(const Fitness& rhs) const;
	virtual bool operator>(const Fitness& rhs) const;
	virtual bool operator<(const Fitness& rhs) const;
	virtual bool operator>=(const Fitness& rhs) const;
	virtual bool operator<=(const Fitness& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Fitness& fitness);

#endif
