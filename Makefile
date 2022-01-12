EXE = main
MOBJ = main.o deque.o simulation.o init.o fighters.o util.o
CC = gcc -Wall
LIBS = -lpthread -lm

main:	$(MOBJ)
	$(CC) -o main $(MOBJ) $(LIBS)

deque.o:	deque.c defs.h init.c
	$(CC) -c deque.c

main.o:	main.c defs.h init.c simulation.c util.c
	$(CC) -c main.c 

simulation.o:	simulation.c init.c defs.h fighters.c util.c
	$(CC) -c simulation.c 

init.o:	init.c defs.h
	$(CC) -c init.c

fighters.o:	fighters.c defs.h
	$(CC) -c fighters.c

util.o:	util.c defs.h
	$(CC) -c util.c

clean:
	rm -f $(EXE) $(MOBJ)
