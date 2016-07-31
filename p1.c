#include "p1.h"
/*
 A (Two Block Horizontal) = 10, B (Two Block Vertical) = 010, C (Four Block Square) = 011
 D (Single Block) = 11, E (Single Block Empty) = 00.
 Test = 0000 0010 1010 1001 0011 1111 1111 0000 (AAAABCDDDDEE)
 
  Test = 0000 0010 1010 1001 0011 1111 1111 0000 (AAAABCDDDDEE)
 
 0000 0110 1010 1001 0011 1111 1111 0000  0x06B6B32B & 0xFC000000 =  0000 0110 1000 0000 ... 0000
 0000 1010 1010 1001 0011 1111 1111 0000  0x0AB6B32B & 0xFC000000 =  0000 1010 1000 0000 ... 0000
 0000 1110 1010 1001 0011 1111 1111 0000  0x0EB6B32B & 0xFC000000
 0001 0010 1010 1001 0011 1111 1111 0000  0x12B6B32B & 0xFC000000
 
 Upto 6_B6B32B
 
 AAD
 CBED
 DE
 AAD
 
 "ABDDACADADEE" 0000 0010 0101 1111 0011 1011 1011 0000(Solution)
 AABDD
 AABCC
 AADCC
 AADEE
 
 0x0000700
 */
#define FINAL_SPOT 8
int validateInput(char *input);
int cSpot(char *dString);
int main( int argc, char *argv[] ){

//    char *start = "AADCBDEDEAAD";//AADCBDEDEAAD
//    FBYTE solution = encode("ABDDACADADEE");
//    
//
//    FBYTE poptracker;
    /*
    FBYTE test = 0x02B6B32B;
    FBYTE test2 = 0x025F3BB0;
    char testEncode[5][13] = {"AADCBDEDEAAD","AAECBDDDEAAD","AADCBEDDEAAD",
        "AADCBDEEDAAD","AADCBDEDDAAE"};
     */
    clock_t tstart = clock(), diff;
    char initial[] = "AADCBDEDEAAD";
	if(argc != 2){
		printf ("ERROR: Invalid input. Terminating program.\n");
		exit(0);
		}
	if(strcmp(argv[1],"1")==0) {
		printf("DEFAULT CASE: AADCBDEDEAAD\n");
	}
    else if(strcmp(argv[1],"2")==0) {
		printf("CASE TWO: DAABEDAACDED\n");
		strcpy(initial, "DAABEDAACDED");
	}
    else if(strcmp(argv[1],"3")==0) {
		printf("CASE THREE: EACADEABDADD\n");
		strcpy(initial, "EACADEABDADD");
	}
	else{
		if(validateInput(argv[1])==1) {
		printf("CUSTOM CASE: %s\n", argv[1]);
		strcpy(initial,argv[1]);
		}
		else {
		printf ("ERROR: Invalid input. Terminating program.\n");
		printf ("A^4*B^1*C^1*D^4*E^2\n");
		exit(0);
		}
	}
    char *start = initial; 
    HASHTABLE allMoves;
    allMoves = *createHashTable(110000);
    
    MOVES movesPossible;
    PATH_NODE * nodeTracker;
    nodeTracker = malloc(sizeof(PATH_NODE));
    PATH_NODE next;
    struct path lastNode;
    int i;
    int moveCount = 0;
    
    nodeTracker->key_value = encode(start);
    pushNodeLast(nodeTracker);
    
    addToHashTable(&allMoves, start);
    
    while ((nodeTracker = popNode()) != NULL){
		if(cSpot(decode(nodeTracker->key_value))==FINAL_SPOT){
            lastNode = *nodeTracker;
            break;
        }
        movesPossible =  *getAllPossible(decode(nodeTracker->key_value));
        for (i = 0; i < movesPossible.size; i++){
            if(addToHashTable(&allMoves, movesPossible.m[i]) != 2){
                next.key_value = encode(movesPossible.m[i]);
                next.previousNode = nodeTracker;
                pushNodeLast(&next);
                addPreviousNode(nodeTracker);
            
            }
        }
    }
    while (lastNode.key_value != encode(start)){
        addStack(lastNode.key_value);
        lastNode = *lastNode.previousNode;
        moveCount++;
    }

    while ((i = popStack()) != -1){
        printf("%s\n", decode(i));
        cls();
        printPuzzle(decode(i), 0);
        //sleep(3); //Slower
        usleep(100000); //Fast
    }

    diff = clock() - tstart;
    
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds.\n With %d Moves\n\n", msec/1000, msec%1000, moveCount);

    
        
    return 0;
}

int validateInput(char *input){
	int counter=0;
	int countA=0;
	int countB=0;
	int countC=0;
	int countD=0;
	int countE=0;
	if(strlen(input)==12){
		for (counter = 0; counter<=12; counter++){
			if (input[counter] == 'A') countA++;
			if (input[counter] == 'B') countB++;
			if (input[counter] == 'C') countC++;
			if (input[counter] == 'D') countD++;
			if (input[counter] == 'E') countE++;
		}
		if(countA==4 && countB==1 && countC==1 && countD==4 && countE==2)
			return 1;
	}
	return 0;
}

int cSpot(char *dString){
	int counter=0;
	int spot=0;
	int x=1;
	int y=1;
	for (counter = 0; dString[counter] != 'C' && y<=2; counter++){
        if (dString[counter] == 'B' && x<=3 && y==1 ){
			spot+= 2;
			x++;
		}	
		else if (dString[counter] == 'B' && x>3 && y==1){
			y+= 2;
			x++;        
		}
		else if (dString[counter] == 'B'){
			spot++;
			x++;            
		}
       	else if (dString[counter] == 'A'){
			spot+=2;
			x+=2;
        }
       	else if (dString[counter] == 'D'||dString[counter] == 'E'){
			spot++;
			x++;       
		}
		if (x>5){
			y++;
			x=0;        
		}
	}   
	return spot;    
}



