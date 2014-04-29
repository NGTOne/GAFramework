#pragma once
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
        virtual int ** crossOver(int genomeOne[], int genomeTwo[], int firstGenomeLength, int secondGenomeLength)=0;
	virtual std::string toString()=0;
};

