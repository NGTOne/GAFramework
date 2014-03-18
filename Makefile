CPPC = g++
CPPFLAGS = -c -g -std=gnu++0x

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
	$(CPPC) $(CPPFLAGS) -Iinclude/core src/core/CrossoverOperation.cpp -o obj/core/CrossoverOperation.o
	$(CPPC) $(CPPFLAGS) -Iinclude/core src/core/MutationOperation.cpp -o obj/core/MutationOperation.o
	$(CPPC) $(CPPFLAGS) -Iinclude/core src/core/Individual.cpp -o obj/core/Individual.o
	$(CPPC) $(CPPFLAGS) -Iinclude/core src/core/GenePool.cpp obj/core -o obj/core/GenePool.o
	$(CPPC) $(CPPFLAGS) -Iinclude/core src/core/NonHierarchicalGenePool.cpp -o obj/core/NonHierarchicalGenePool.o
	$(CPPC) $(CPPFLAGS) -Iinclude/core src/core/SelectionStrategy.cpp -o obj/core/SelectionStrategy.o
	$(CPPC) $(CPPFLAGS) -Iinclude/core src/core/HierarchicalGenePool.cpp -o obj/core/HierarchicalGenePool.o

selections:
	mkdir -p obj/selections
	make tournamentSelection

mutations:
	mkdir -p obj/mutations
	make bitwiseMutation

crossovers:
	mkdir -p obj/crossovers
	make twoPointCrossover

tournamentSelection:
	$(CPPC) $(CPPFLAGS) -Iinclude/core src/selections/TournamentSelection.cpp -o obj/selections/TournamentSelection.o

bitwiseMutation:
	$(CPPC) $(CPPFLAGS) -Iinclude/core -Iinclude/mutations src/mutations/BitwiseMutation.cpp -o obj/mutations/BitwiseMutation.o

twoPointCrossover:
	$(CPPC) $(CPPFLAGS) -Iinclude/core -Iinclude/crossovers src/crossovers/TwoPointCrossover.cpp -o obj/crossovers/TwoPointCrossover.o

clean:
	rm -f obj/*/*
