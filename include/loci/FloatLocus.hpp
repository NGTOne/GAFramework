#include "../core/Locus.hpp"
#include <vector>
#include <string>
#pragma once

class FloatLocus: public Locus {
	private:

	protected:

	public:
	FloatLocus(float bottom, float top, float resolution);
	FloatLocus(std::vector<float> values);

	float getIndex(int index);

	~FloatLocus();

	std::string toString();
	std::string flatten(int index);
};
