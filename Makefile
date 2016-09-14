CPPC = g++
CPPFLAGS = -c -g -std=gnu++0x -fPIC -Wall -Werror -pedantic-errors

SHELL := /bin/bash
PLATFORM := $(shell uname -s)

ifeq ($(PLATFORM), Linux)
SHAREDLIB = -lHierGA
LIBNAME = libHierGA.so
EIGEN = -I/usr/include/eigen3
else ifeq ($(PLATFORM), Darwin)
SHAREDLIB = -L/usr/local/lib -lHierGA
LIBNAME = libHierGA.dylib
EIGEN = -I/usr/local/include/eigen3
endif

EXAMPLEINCLUDE = -I/usr/local/include -Isrc/examples/include $(EIGEN)

all: library

install: uninstall all-header
	sudo cp libs/$(LIBNAME) /usr/local/lib
	sudo chmod 0755 /usr/local/lib/$(LIBNAME)
	sudo mkdir /usr/local/include/libHierGA
	sudo cp -r include/* /usr/local/include/libHierGA
	if [[ "$$(uname -s)" == "Linux" ]]; then sudo ldconfig; fi

all-header:
	echo "#ifndef HIERGA" > include/HierGA.hpp
	echo "#define HIERGA" >> include/HierGA.hpp
	find include -name *.hpp | grep -v HierGA | sed 's/^include\///g' | \
		awk '{print "#include \"" $$1 "\""}' >> include/HierGA.hpp
	echo "#endif" >> include/HierGA.hpp

uninstall:
	sudo rm -f /usr/local/lib/*libHierGA*
	sudo rm -rf /usr/local/include/*libHierGA*
	if [[ "$$(uname -s)" == "Linux" ]]; then sudo ldconfig; fi

library: obj-dir
	./compile-scripts/make-lib.sh

obj-dir:
	./compile-scripts/make-obj-dir.sh

# Examples
examples: example-fitnesses
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/1max.cpp -o obj/examples/1max.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/Sphere.cpp -o obj/examples/Sphere.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/Hier1max.cpp -o obj/examples/Hier1max.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/LongestFragment.cpp -o obj/examples/LongestFragment.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/HierLongestFragment.cpp -o obj/examples/HierLongestFragment.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/ApportioningHierLF.cpp -o obj/examples/ApportioningHierLF.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/MetaHierLF.cpp -o obj/examples/MetaHierLF.o
	$(CPPC) -o examples/1max obj/examples/1max.o obj/examples/fitnesses/1maxFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/Sphere obj/examples/Sphere.o obj/examples/fitnesses/SphereFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/Hier1max obj/examples/Hier1max.o obj/examples/fitnesses/1maxFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/LongestFragment obj/examples/LongestFragment.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/HierLongestFragment obj/examples/HierLongestFragment.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/ApportioningHierLF obj/examples/ApportioningHierLF.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/MetaHierLF obj/examples/MetaHierLF.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)

example-fitnesses:
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/fitnesses/1maxFitness.cpp -o obj/examples/fitnesses/1maxFitness.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/fitnesses/SphereFitness.cpp -o obj/examples/fitnesses/SphereFitness.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/fitnesses/LongestFragmentFitness.cpp -o obj/examples/fitnesses/LongestFragmentFitness.o

hier3longestfragment:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3LongestFragment src/examples/Hier3LongestFragment/LongestFragmentFitness.cpp -o obj/examples/Hier3LongestFragment/LongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3LongestFragment src/examples/Hier3LongestFragment/HierLongestFragmentFitness.cpp -o obj/examples/Hier3LongestFragment/HierLongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3LongestFragment src/examples/Hier3LongestFragment/HierLongestFragment.cpp -o obj/examples/Hier3LongestFragment/HierLongestFragment.o
	$(CPPC) -o examples/Hier3LongestFragment obj/examples/Hier3LongestFragment/*.o $(SHAREDLIB)

hier3proprr:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3PropLF src/examples/Hier3PropLF/LongestFragmentFitness.cpp -o obj/examples/Hier3PropLF/LongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3PropLF src/examples/Hier3PropLF/HierLongestFragmentFitness.cpp -o obj/examples/Hier3PropLF/HierLongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3PropLF src/examples/Hier3PropLF/HierLongestFragment.cpp -o obj/examples/Hier3PropLF/HierLongestFragment.o
	$(CPPC) -o examples/Hier3PropLF obj/examples/Hier3PropLF/*.o $(SHAREDLIB)

clean:
	find obj -name *.o | xargs rm -f
	rm -f libs/*
	cd examples; ls | xargs rm -f
	rm -f /usr/libs/libHierGA.so*
