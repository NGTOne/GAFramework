#pragma once
#include "../../core/Genome.hpp"
#include <random>
#include <string>
#include <vector>

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
	void init(unsigned seed);
        CrossoverOperation();        
        CrossoverOperation(unsigned seed);
        virtual std::vector<Genome*> crossOver(std::vector<Genome*> genomes)=0;
	virtual std::string toString()=0;
};

