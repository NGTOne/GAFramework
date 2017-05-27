#ifndef CORE_Fitness
#define CORE_Fitness

#include <vector>
#include <initializer_list>

class Fitness {
	private:

	protected:
	std::vector<double> components;

	public:
	Fitness();
	Fitness(double initial);
	Fitness(std::initializer_list<double> initial);

	void drop();
	void drop(unsigned int index);
	void drop(unsigned int start, unsigned int end);
	void drop(std::initializer_list<unsigned int> indices);

	void add(double component);
	void add(std::initializer_list<double> components);

	virtual double collapse();
	std::vector<double> getComponents();

	virtual bool operator==(const Fitness& rhs);
	virtual bool operator!=(const Fitness& rhs);
	virtual bool operator>(const Fitness& rhs);
	virtual bool operator<(const Fitness& rhs);
	virtual bool operator>=(const Fitness& rhs);
	virtual bool operator<=(const Fitness& rhs);
};

#endif
