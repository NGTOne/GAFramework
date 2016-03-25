#include "../core/LibraryNode.hpp"
#include <vector>
#include <string>
#pragma once

class IntLocus: public LibraryNode<int> {
	private:

	protected:

	public:
	IntLocus(int bottom, int top);
	IntLocus(std::vector<int> values);

	~IntLocus();

	std::string toString();
};
