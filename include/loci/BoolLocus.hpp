#include "CollectionLocus.hpp"
#include <vector>
#include <string>
#pragma once

class BoolLocus: public CollectionLocus {
	private:

	protected:

	public:
	BoolLocus();
	~BoolLocus();

	bool getIndex(Gene* index);

	std::string toString();
	std::string flatten(Gene* index);
};
