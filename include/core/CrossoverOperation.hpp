#pragma once
#include "Genome.hpp"
#include <random>
#include <string>

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

