#include "CollectionLocus.hpp"
#include <vector>
#include <initializer_list>
#include <string>
#pragma once

class IntCollectionLocus: public CollectionLocus {
	private:

	protected:

	public:
	IntCollectionLocus(int bottom, int top, int interval=1);
	IntCollectionLocus(std::vector<int> values);
	IntCollectionLocus(std::initializer_list<int> values);

	~IntCollectionLocus();

	std::string toString();
	std::string flatten(Gene* index);
};
