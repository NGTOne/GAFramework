info:
	@echo "Usage:"
	@echo "make examples: Produces a series of example GAs and HGAs using the framework"
	@echo "make library: Rebuilds the library from scratch"
	@echo "make core: Produces the object files for the \"core\" components"
	@echo "make selections: Produces the object files for the selection strategies"
	@echo "make mutations: Produces the object files for the mutation operators"
	@echo "make crossovers: Produces the object files for the crossover operators"
	@echo ""
	@echo "Any GA/HGA needs at least core, and one component from each of selections, mutations, and crossovers in order to function."

examples: library

library: core selections mutations crossovers

core:
	mkdir -p obj
	mkdir -p obj/core
	g++ -c -g -Iinclude/core -std=gnu++0x src/core/CrossoverOperation.cpp -o obj/core/CrossoverOperation.o
	g++ -c -g -Iinclude/core -std=gnu++0x src/core/MutationOperation.cpp -o obj/core/MutationOperation.o
	g++ -c -g -Iinclude/core -std=gnu++0x src/core/Individual.cpp -o obj/core/Individual.o
	g++ -c -g -Iinclude/core -std=gnu++0x src/core/GenePool.cpp obj/core -o obj/core/GenePool.o
	g++ -c -g -Iinclude/core -std=gnu++0x src/core/NonHierarchicalGenePool.cpp -o obj/core/NonHierarchicalGenePool.o
	g++ -c -g -Iinclude/core -std=gnu++0x src/core/SelectionStrategy.cpp -o obj/core/SelectionStrategy.o
	g++ -c -g -Iinclude/core -std=gnu++0x src/core/HierarchicalGenePool.cpp -o obj/core/HierarchicalGenePool.o

selections: tournamentSelection

mutations: bitwiseMutation

crossovers: twoPointCrossover

tournamentSelection:
	g++ -c -g src/selections/TournamentSelection.cpp obj/selections

bitwiseMutation:
	g++ -c -g src/mutations/BitwiseMutation.cpp obj/mutations

twoPointCrossover:
	g++ -c -g src/crossovers/TwoPointCrossover.cpp obj/crossovers

clean:
	rm -f obj/*/*
