# ConcurrentSystems
# Running
Compile code using make, the project report is contained within the docs folder
# Assignment Description
CSU33014 Lab: The Travelling Salesperson

Alex is a travelling salesperson who must visit several cities around the
country in a sales trip. Alex wants to minimize the total travel distance,by finding the shortest route that visits
each city exactly once. Alex hopes that a computer might be able to help find the shortest route.

The travelling salesperson problem (TSP) is a classic computer science problem
that is computationally intractable for large numbers of cities. For
this reason, heuristics are normally used which are not guaranteed to
find the shortest route, but instead try to find some appoximation of
it. One of the most common approaches is the nearest neighbour heuristic.

We have some existing code to implement the nearest neighbour
heuristic.  Your job is to make it run fast on the machine
stoker.cs.tcd.ie. The purpose of the exercise is to gain a better
understanding of optimization and computer architecture by working
with real code.

The lab submission should take the form of a working,
commented piece of code that is no worse written than is necessary for the optimizations that you implement. The first page of the code should include a comment with a description of the efforts made to make the code
efficient.

The code to be optimized is in two files:
sales.c
mytour.c

The first file is a test harness, which sets up the data, invokes
your routine, checks that you get the same answer as the original
code, and reports execution times. You should not modify the test
harness file. When it comes to testing the speed of your code, we may
even use a slightly different test harness file, but we will maintain
the interfaces.

Note that the files sales.c uses C maths libraries, and depending on
your compiler, you may need to pass an additional parameter "-lm" to
the compiler at the command line.

The second file contains the function "my_tour". This is where you
should write your code. In the version that you download from the
website, this function simply calls simple_find_tour. But you should
write your own code in here. You may want to base your code on
simple_find_tour or you may want to write your own code entirely.

Note that whatever code you write to compute your tour, you must get
the same result as simple_find_tour. This means that you must use the
nearest neighbour heuristic, and you must use the same starting city
as simple_find_tour. The test harness checks that your code produces
the same tour as simple_find_tour. We will avoid inputs where the
distances between cities is the same (or almost the same) which might
result in different answers due to order of evaluation or floating
point imprecision.

For testing the speed of your code, we will use a variety of problem
sizes, and we may, potentially, use a different method for generating
inputs than the current test harness. The machine is
stoker.cs.tcd.ie. This machine has two processors.  Each processor has
two out-of-order pipelined, superscalar cores.  Each core has its own
L1 cache, and there is a single L2 cache that is shared by both cores
on a single processor.

You may use whichever C compiler flags you like for compiling your
code.  The compiler and the flags should be documented in your code.
