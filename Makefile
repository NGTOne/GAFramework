info:
	@echo "Usage:"
	@echo "make examples: Produces a series of example GAs and HGAs using the framework"
	@echo "make core: Produces the object files for the \"core\" components"
	@echo "make selections: Produces the object files for the selection strategies"
	@echo "make mutations: Produces the object files for the mutation operators"
	@echo "make crossovers: Produces the object files for the crossover operators"
	@echo ""
	@echo "Any GA/HGA needs at least core, and one component from each of selections, mutations, and crossovers in order to function."

examples: core selections mutations crossovers

core:
	g++ -c -g src/core/*.cpp obj/core

selections: core tournamentSelection

mutations: core bitwiseMutation

crossovers: core twoPointCrossover

tournamentSelection: core
	g++ -c -g src/selections/TournamentSelection.cpp obj/selections

bitwiseMutation: core
	g++ -c -g src/mutations/BitwiseMutation.cpp obj/mutations

twoPointCrossover: core
	g++ -c -g src/crossovers/TwoPointCrossover.cpp obj/crossovers
