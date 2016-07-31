#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#ifndef _p1_h
#define _p1_h
/*
 A (Two Block Horizontal) = 10, B (Two Block Vertical) = 010, C (Four Block Square) = 011
 D (Single Block) = 11, E (Single Block Empty) = 00.
 Test = 10010011110010010011110010 (ABCDABCDA)

 5 columns  and 4 rows:
 A = 2 column block and 1 row block.
 B = 1 column black and 2 row block.
 C = 2 column block and 2 row block.
 D = 1 column block and 1 row block.
 E = 1 column block and 1 row block.
 
 Initial position:
 1) AADCBDEDEAAD
 
 Next Possible:
 1-A) AAECBDDDEAAD
    1-A-1) AAECBDDDDAAE (is the same as 1-D-1)
    1-A-2) AEACBDDDEAAD
    1-A-3) AAECBDDEDAAD
    1-A-4) AAECBDEDDAAD
 
 1-B) AADCBDEDEAAE
 
 1-C) AADCBEDDEAAD
 
 1-D) AADCBDEDDAAE
    1-D-1) AAECBDDDDAAE
 
 
 
 */
#define COMPARE 0x2000000 /* COMPARE is the bit in 26th position*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

#define cls() printf( "\033[H\033[J" )
#define position(row,col) printf( "\033[%d;%dH", (row), (col) )
#define position_flush(row,col) printf( "\033[%d;%dH", (row), (col) )
/*Global Variables */
unsigned int currentState;
typedef unsigned char BYTE;
typedef unsigned int FBYTE;
char charSequence[13];

/*Structures */
typedef struct list{
    unsigned int val;
    char *str;
    struct list *next;
} LINKEDLIST;
typedef struct path{
    FBYTE key_value;
    struct path *previousNode;
}PATH_NODE;

typedef struct nodelist{
    PATH_NODE * val;
    struct nodelist *next;
} NODELIST;


struct node{
    int key_value;
    char letter;
    struct node *left, *right;
};
typedef struct hashT{
    int size;
    LINKEDLIST **table;
} HASHTABLE;

typedef struct position_moves{
    int size;
    char ** m;
}MOVES;
// allLterts[0].letter = 'A'  allLterts[0].letterPlace = 2 is the second place in the letter
typedef struct letter{
    int letterPlace;
    char letter;
}LETTERA;

typedef struct letterE{
    int pos[4], epos;
    char left, top, right, bottom;
}EMPTY;



EMPTY emptySpot[2];
struct node huffTree[9];




/* Huffman Tree Functions Prototypes */
void buildTree();
char *decode(FBYTE);
FBYTE encode(char *);

/*Genereal Puzzle Functions */
void printPuzzle(char *, int);
/*Print will take an option of 0 to print and
 anyhting else will just create a data structure.
 */

/*Queue Functions */
void addToQueue(FBYTE a);
FBYTE popQueue();


/*Linked List Functions Prototypes */
void add(unsigned int );
void print_list();
void pushTail(unsigned int);
unsigned int pop();

/*Hash Table variables */
LINKEDLIST hashList;
unsigned int tableSize;
/* Stack functions */
void addStack(unsigned int );
unsigned int popStack();

/*Hash fucntions prototypes*/
unsigned int hash(HASHTABLE *ht, char *s);
HASHTABLE *createHashTable(unsigned long);
LINKEDLIST *lookup(HASHTABLE *, char *);
int addToHashTable(HASHTABLE *, char *);
void freeTable(HASHTABLE *);
/* Data Manipulation */
MOVES * getAllPossible(char *pstr);

/*Node Queue Functions */
void pushNodeLast(PATH_NODE *);
PATH_NODE * popNode();
void addPreviousNode(PATH_NODE *);


#endif
