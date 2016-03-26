#include "../core/LibraryNode.hpp"
#include <vector>
#include <string>
#pragma once

class FloatLocus: public LibraryNode<float> {
	private:

	protected:

	public:
	FloatLocus(float bottom, float top, float resolution);
	FloatLocus(std::vector<float> values);

	~FloatLocus();

	std::string toString();
};
