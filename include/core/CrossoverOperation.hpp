#pragma once
#include "Genome.hpp"
#include <random>
#include <string>

//The CrossoverOperation abstract class is exactly what it says on the
//tin - it serves as a base class for all manner of possible GA crossover
//operators.
//TODO: Make n-parent crossovers possible
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

