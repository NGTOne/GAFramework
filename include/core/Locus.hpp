#include <string>
#include <vector>
#include <boost/any.hpp>
#pragma once

class Locus {
	private:

	protected:
	std::vector<boost::any> population;

	Locus();
	Locus(std::vector<boost::any> population);

	public:
	~Locus();

	int randomIndex();
	boost::any getIndex(int index);

	virtual std::string toString();
};

