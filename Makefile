CPPC = g++
CPPFLAGS = -c -g -std=gnu++0x -fPIC
CORE = -Iinclude/core
SELS = -Iinclude/selections
CROSS = -Iinclude/crossovers
MUTS = -Iinclude/mutations
GENS = -Iinclude/generations
ENDS = -Iinclude/endconditions
ALLINCLUDES = $(CORE) $(SELS) $(CROSS) $(MUTS) $(GENS) $(ENDS)
STATICLIB = libs/libGAFramework.a
MAJORVERSION = 1
MINORVERSION = 0
LIBNAME = libGAFramework.so
DYNAMICLIB = $(LIBNAME).$(MAJORVERSION).$(MINORVERSION)

SHAREDLIB = -lGAFramework -IGAFramework

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

all: examples

install:
	sudo cp libs/$(LIBNAME) /usr/lib
	sudo chmod 0755 /usr/lib/$(LIBNAME)
	sudo mkdir /usr/include/libGAFramework
	sudo cp -r include/* /usr/include/libGAFramework
	sudo ldconfig

uninstall:
	sudo rm /usr/lib/*libGAFramework*
	sudo rm -r /usr/include/*libGAFramework*
	sudo ldconfig

examples: library 1-max hier1-max royalroad hierroyalroad hier3royalroad

library: core selections mutations crossovers generations endconditions
	g++ -shared -o libs/$(LIBNAME) obj/*/*.o
	ar -cvq $(STATICLIB) obj/*/*.o

core:
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/CrossoverOperation.cpp -o obj/core/CrossoverOperation.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/MutationOperation.cpp -o obj/core/MutationOperation.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/Genome.cpp -o obj/core/Genome.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/Individual.cpp -o obj/core/Individual.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/GenePool.cpp -o obj/core/GenePool.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/NonHierarchicalGenePool.cpp -o obj/core/NonHierarchicalGenePool.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/SelectionStrategy.cpp -o obj/core/SelectionStrategy.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/GenerationModel.cpp -o obj/core/GenerationModel.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/EndCondition.cpp -o obj/core/EndCondition.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/core/HierarchicalGenePool.cpp -o obj/core/HierarchicalGenePool.o

selections: tournamentSelection

mutations: uniformMutation boundaryMutation

crossovers: nPointCrossover uniformCrossover cutAndSpliceCrossover

generations: ga es ssga

endconditions: fitnessMatch

ga:
	$(CPPC) $(CPPFLAGS) $(CORE) $(GENS) src/generations/GAGeneration.cpp -o obj/generations/GAGeneration.o

es:
	$(CPPC) $(CPPFLAGS) $(CORE) $(GENS) src/generations/ESGeneration.cpp -o obj/generations/ESGeneration.o

ssga:
	$(CPPC) $(CPPFLAGS) $(CORE) $(GENS) src/generations/SSGAGeneration.cpp -o obj/generations/SSGAGeneration.o

tournamentSelection:
	$(CPPC) $(CPPFLAGS) $(CORE) $(SELS) src/selections/TournamentSelection.cpp -o obj/selections/TournamentSelection.o

uniformMutation:
	$(CPPC) $(CPPFLAGS) $(CORE) $(MUTS) src/mutations/UniformMutation.cpp -o obj/mutations/UniformMutation.o

boundaryMutation:
	$(CPPC) $(CPPFLAGS) $(CORE) $(MUTS) src/mutations/BoundaryMutation.cpp -o obj/mutations/BoundaryMutation.o

nPointCrossover:
	$(CPPC) $(CPPFLAGS) $(CORE) $(CROSS) src/crossovers/NPointCrossover.cpp -o obj/crossovers/NPointCrossover.o

uniformCrossover:
	$(CPPC) $(CPPFLAGS) $(CORE) $(CROSS) src/crossovers/UniformCrossover.cpp -o obj/crossovers/UniformCrossovers.o

cutAndSpliceCrossover:
	$(CPPC) $(CPPFLAGS) $(CORE) $(CROSS) src/crossovers/CutAndSpliceCrossover.cpp -o obj/crossovers/CutAndSpliceCrossover.o

fitnessMatch:
	$(CPPC) $(CPPFLAGS) $(CORE) $(ENDS) src/endconditions/FitnessMatchEnd.cpp -o obj/endconditions/FitnessMatchEnd.o

1-max:
	$(CPPC) $(CPPFLAGS) src/examples/1max/1maxFitness.cpp -o obj/examples/1max/1maxFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/1max src/examples/1max/1max.cpp -o obj/examples/1max/1max.o
	$(CPPC) -o examples/1max obj/examples/1max/*.o

hier1-max:
	$(CPPC) $(CPPFLAGS) $(CORE) src/examples/Hier1max/1maxFitness.cpp -o obj/examples/Hier1max/1maxFitness.o
	$(CPPC) $(CPPFLAGS) $(CORE) src/examples/Hier1max/Hier1maxFitness.cpp -o obj/examples/Hier1max/Hier1maxFitness.o
	$(CPPC) $(CPPFLAGS) $(ALLINCLUDES) -Isrc/examples/Hier1max src/examples/Hier1max/Hier1max.cpp -o obj/examples/Hier1max/Hier1max.o
	$(CPPC) -o examples/Hier1max obj/examples/Hier1max/*.o $(STATICLIB)

royalroad:
	$(CPPC) $(CPPFLAGS) $(CORE) src/examples/RoyalRoad/RoyalRoadFitness.cpp -o obj/examples/RoyalRoad/RoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) $(ALLINCLUDES) -Isrc/examples/RoyalRoad src/examples/RoyalRoad/RoyalRoad.cpp -o obj/examples/RoyalRoad/RoyalRoad.o
	$(CPPC) -o examples/RoyalRoad obj/examples/RoyalRoad/*.o $(STATICLIB)

hierroyalroad:
	$(CPPC) $(CPPFLAGS) $(CORE) -Isrc/examples/HierRoyalRoad src/examples/HierRoyalRoad/RoyalRoadFitness.cpp -o obj/examples/HierRoyalRoad/RoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) $(CORE) -Isrc/examples/HierRoyalRoad src/examples/HierRoyalRoad/HierRoyalRoadFitness.cpp -o obj/examples/HierRoyalRoad/HierRoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) $(ALLINCLUDES) -Isrc/examples/HierRoyalRoad src/examples/HierRoyalRoad/HierRoyalRoad.cpp -o obj/examples/HierRoyalRoad/HierRoyalRoad.o
	$(CPPC) -o examples/HierRoyalRoad obj/examples/HierRoyalRoad/*.o $(STATICLIB)

hier3royalroad:
	$(CPPC) $(CPPFLAGS) $(CORE) -Isrc/examples/Hier3RoyalRoad src/examples/Hier3RoyalRoad/RoyalRoadFitness.cpp -o obj/examples/Hier3RoyalRoad/RoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) $(CORE) -Isrc/examples/Hier3RoyalRoad src/examples/Hier3RoyalRoad/HierRoyalRoadFitness.cpp -o obj/examples/Hier3RoyalRoad/HierRoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) $(ALLINCLUDES) -Isrc/examples/Hier3RoyalRoad src/examples/Hier3RoyalRoad/HierRoyalRoad.cpp -o obj/examples/Hier3RoyalRoad/HierRoyalRoad.o
	$(CPPC) -o examples/Hier3RoyalRoad obj/examples/Hier3RoyalRoad/*.o $(STATICLIB)


clean:
	find obj -name *.o | xargs rm -f
	rm -f libs/*
	cd examples; ls | xargs rm -f
	rm -f /usr/libs/libGAFramework.so*
