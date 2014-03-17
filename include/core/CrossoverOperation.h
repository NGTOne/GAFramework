class CrossoverOperation {
        private:

        protected:
        unsigned seed;

        public:
        CrossoverOperation();        
        CrossoverOperation(int newSeed, int newCrossoverRate);
        int ** crossOver(int genomeOne[], int genomeTwo[], int firstGenomeLength, int secondGenomeLength);
};

