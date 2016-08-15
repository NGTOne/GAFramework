#ifndef LOCI_BoolLocus
#define LOCI_BoolLocus

#include "CollectionLocus.hpp"
#include <vector>
#include <string>

class BoolLocus: public CollectionLocus {
	private:

	protected:

	public:
	BoolLocus();
	~BoolLocus();

	std::string toString();
	std::string flatten(Gene* index);
};

#endif
