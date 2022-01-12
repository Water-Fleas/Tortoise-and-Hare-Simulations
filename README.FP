author: William Yin
purpose: simulate the fight between two heroes and a band of pirates, in a few scenarios over several runs
source files: deque.c, fighters.c simulation.c init.c main.c util.c
header files: defs.h

to compile: type "make" in the command line in a folder with the makefile and all the aforementioned files
to run: type ./main followed by an integer argument to note the amount of runs wanted. For example, typing
./main 45 will run the program with 45 runs. If the integer argument is not provided it will default to 100.