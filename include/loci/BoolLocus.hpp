#include "../core/Locus.hpp"
#include <vector>
#include <string>
#pragma once

class BoolLocus: public Locus {
	private:

	protected:

	public:
	BoolLocus();

	bool getIndex(unsigned int index);

	~BoolLocus();

	std::string toString();
	std::string flatten(unsigned int index);
};
