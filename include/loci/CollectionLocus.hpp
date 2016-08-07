#include "../core/Locus.hpp"
#include <vector>

class CollectionLocus : public Locus {
	private:

	protected:
	std::vector<boost::any> population;

	CollectionLocus();
	CollectionLocus(std::vector<boost::any> population);
	void setPopulation(std::vector<boost::any> population);

	public:
	virtual ~CollectionLocus();
	virtual Gene* getGene();
	virtual Gene* getGene(double index);

	virtual double randomIndex();
	virtual double topIndex();
	virtual double bottomIndex();
	virtual double closestIndex(double index);
	virtual bool outOfRange(double index);
	virtual std::string toString()=0;
	virtual std::string flatten(Gene* index)=0;
	virtual boost::any getIndex(Gene* index);
}
