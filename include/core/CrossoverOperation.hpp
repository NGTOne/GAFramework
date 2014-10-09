#pragma once
#include "Genome.hpp"
#include <random>
#include <string>

/*
* This class serves as an abstract base for crossover operators, allowing
* us to create whatever crossover operators we need to.
*/

/*
* TODO: Rework it to allow n-parent crossover, rather than being limited to
*       two parents
*/

class CrossoverOperation {
        private:

        protected:
        unsigned seed;
	std::mt19937 generator;

        public:
	void init(unsigned newSeed);
        CrossoverOperation();        
        CrossoverOperation(unsigned newSeed);
        virtual Genome ** crossOver(Genome * genomeOne, Genome * genomeTwo)=0;
	virtual std::string toString()=0;
};

