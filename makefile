#Name: Joshua Villasenor, Luke Carpenter, Kristian Pugal
#Class: CS560, Spring 2015
#Assignment #1, Block Solver
#File Name: p1.c, p1.h


PROGRAM = p1
CC = gcc
CFLAGS = -g -Wall


${PROGRAM}:	p1.o 	functions.o	tree.o	hashtable.o	stack.o		nodeQueue.o
		${CC} -o p1 p1.o functions.o tree.o hashtable.o stack.o nodeQueue.o
		
p1.o:		p1.h	

functions.o: 	functions.c	

tree.o:		tree.c

hashtable.o:	hashtable.c

nodeQueue.o:	nodeQueue.c

clean:
		rm -f *.o ${PROGRAM}


