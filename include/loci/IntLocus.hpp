#include "../core/Locus.hpp"
#include <vector>
#include <string>
#pragma once

class IntLocus: public Locus {
	private:

	protected:

	public:
	IntLocus(int bottom, int top);
	IntLocus(std::vector<int> values);

	int getIndex(unsigned int index);

	~IntLocus();

	std::string toString();
	std::string flatten(unsigned int index);
};
