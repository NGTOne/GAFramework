#include <string>
#include <vector>
#pragma once

template <typename T>
class Locus {
	private:

	protected:
	std::vector<T> population;

	Locus();

	public:
	Locus(std::vector<T> population);
	~Locus();

	T getIndex(int index);

	virtual std::string toString();
};

