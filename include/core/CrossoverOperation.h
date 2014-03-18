#pragma once

class CrossoverOperation {
        private:

        protected:
        unsigned seed;

        public:
        CrossoverOperation();        
        CrossoverOperation(int newSeed, int newCrossoverRate);
        virtual int ** crossOver(int genomeOne[], int genomeTwo[], int firstGenomeLength, int secondGenomeLength)=0;
};

