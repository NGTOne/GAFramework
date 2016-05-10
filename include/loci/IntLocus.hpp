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

	int getIndex(int index);

	~IntLocus();

	std::string toString();
};
