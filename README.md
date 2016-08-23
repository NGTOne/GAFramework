libHierGA
===========
Sebastian Lenartowicz's Hierarchical Genetic Algorithms Library

This framework provides a basic library for basic and hierarchical genetic
algorithms. It is completely function-agnostic, and the only thing that it
needs to start running is a fitness function (or a set of them), and an
appropriately constructed GA.

PLEASE NOTE: All examples are designed to be quite verbose while running, and
the output should be sent to a file for reading and interpretation. For
instance, the simplest example, 1max, outputs around 8,000 lines of text.

### Dependencies

gcc 4.6.3 or later (requires support for --std=gnu++0x)
Boost 1.58 or later
Eigen 3.2.2-3 or later
