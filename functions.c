#include "p1.h"

/*
 A (Two Block Horizontal) = 10, B (Two Block Vertical) = 010, C (Four Block Square) = 011
 D (Single Block) = 11, E (Single Block Empty) = 00.
 Test = 0000 0010 1010 1001 0011 1111 1111 0000 (AAAABCDDDDEE)
 
 "ABDDACADADEE" (Solution)
 "AADCBDEDEAAD" (Start)
 */
char grid [6][7], copyGrid [6][7];
int positionERow[2], positionEColumn[2],pCC[4], pCR[4], pBC, pBR, pBCB, pBRB, pAR, pAC;
int posAC[2], posAR[2];

char * cswapPositions(char * strSwap, int targetR, int targetC,int targetR2, int targetC2, int destR, int destC,int destR2, int destC2){
    char temp;
    int i, j, k =0;
    
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            copyGrid[i][j] = grid[i][j];
        }
    }
    
    if (targetC2 == 0) {
        temp = copyGrid[targetR][targetC];
        copyGrid[targetR][targetC] = copyGrid[destR][destC];
        copyGrid[destR][destC] = temp;
    }
    else{
        
        temp = copyGrid[targetR][targetC];
        copyGrid[targetR][targetC] = copyGrid[destR][destC];
        copyGrid[destR][destC] = temp;
        
        temp = copyGrid[targetR2][targetC2];
        copyGrid[targetR2][targetC2] = copyGrid[destC2][destC2];
        copyGrid[destR2][destC2] = temp;

    }
    for (i = 1; i < 5; i++) {
        for (j = 1; j < 6; j++) {
            if (copyGrid[i][j] == 'A'){
                copyGrid[i][j] = 0;
                copyGrid[i][j+1] = 0;
                strSwap[k] = 'A';
                k++;
            }
            if (copyGrid[i][j] == 'B'){
                copyGrid[i][j] = 0;
                copyGrid[i+1][j] = 0;
                strSwap[k] = 'B';
                k++;
            }
            if (copyGrid[i][j] == 'C'){
                copyGrid[i][j] = 0;
                copyGrid[i+1][j] = 0;
                copyGrid[i][j+1] = 0;
                copyGrid[i+1][j+1] = 0;
                strSwap[k] = 'C';
                k++;
            }
            if (copyGrid[i][j] == 'D') {
                copyGrid[i][j] = 0;
                strSwap[k] = 'D';
                k++;
            }
            if (copyGrid[i][j] == 'E') {
                copyGrid[i][j] = 0;
                strSwap[k] = 'E';
                k++;
            }
            
        }
    }
    
    

	return strSwap;
}

void printPuzzle(char *state, int option){
    int incrementer, occr =1, occurT = 0;
    int positionColumn = 1, positionRow = 1, row = 1, column = 1, eTracker = 0;
    
    memset(grid,0,sizeof(grid));
    int positionGrid [6][7];
    memset(positionGrid,-1,sizeof(positionGrid));
    
    
    for (incrementer = 0; incrementer < 12; incrementer++) {
        /* Switch all fives to 7 and all rows to 6 the start is back to one */
        if( state[incrementer] == 'A'){
            while(grid [row][column] != 0 && column < 6 && row < 5){
                column++;
                if (column == 6) {
                    column = 1;
                    row++;
                }
            }
            if (column == 5) {
                column = 1;
                while(grid [row+1][occr] != 0 && occr < 6 && row+occurT < 5)
                    occr++;
                pAC = occr; pAR = row + 1;
                posAC[0] = occr; posAR[0] = row + 1;
                posAC[1] = occr + 1; posAR[1] = row + 1;
                
                grid [row+1][occr] = 'A';
                grid [row+1][occr+1] = 'A';
                positionGrid [row+1][column] = incrementer;
                positionGrid [row+1][column+1] = incrementer;
                occurT++;
                column += 2;
            }
            else{
                pAC = row; pAR = column;
                posAC[0] = column; posAR[0] = row ;
                posAC[1] = column + 1; posAR[1] = row;
                
                grid [row][column] = 'A';
                grid [row][column+1] = 'A';
                positionGrid [row][column] = incrementer;
                positionGrid [row][column+1] = incrementer;
                
            }
            if (column == 6) {
                column = 1;
                row++;
            }
        
        }
        if( state[incrementer] == 'B'){
            while(grid [row][column] != 0 && column < 6 && row < 5){
                column++;
                if (column == 6) {
                    column = 1;
                    row++;
                }
            }
            pBC = column; pBR = row;
            pBCB = column; pBRB = row + 1;
            
            grid [row][column] = 'B';
            grid [row+1][column] = 'B';
            positionGrid [row][column] = incrementer;
            positionGrid [row+1][column] = incrementer;
            column++;
            if (column == 6) {
                column = 1;
                row++;
            }
            
        }
        if( state[incrementer] == 'C'){
            while(grid [row][column] != 0 && column < 6 && row < 5){
                column++;
                if (column == 6) {
                    column = 1;
                    row++;
                }
            }
            if (column == 5) {
                column = 1;
                pCC[0] = column; pCC[1] = column+1;         pCR[0] = row +1; pCR[1] = row +1;
                pCC[2] = column; pCC[3] = column+1;         pCR[2] = row +2; pCR[3] = row +2;
                
                grid [row+1][column] = 'C';
                grid [row+1][column+1] = 'C';
                grid [row+2][column] = 'C';
                grid [row+2][column+1] = 'C';

                positionGrid [row+1][column] = incrementer;
                positionGrid [row+1][column+1] = incrementer;
                positionGrid [row+2][column] = incrementer;
                positionGrid [row+2][column+1] = incrementer;
                column ++;
            }
            else{
                pCC[0] = column; pCC[1] = column+1;         pCR[0] = row; pCR[1] = row;
                pCC[2] = column; pCC[3] = column+1;         pCR[2] = row +1; pCR[3] = row +1;
                
                grid [row][column] = 'C';
                grid [row][column+1] = 'C';
                grid [row+1][column] = 'C';
                grid [row+1][column+1] = 'C';
                positionGrid [row][column] = incrementer;
                positionGrid [row][column+1] = incrementer;
                positionGrid [row+1][column] = incrementer;
                positionGrid [row+1][column+1] = incrementer;
                column++;
            }
            if (column == 6) {
                column = 1;
                row++;
            }
        }
        if( state[incrementer] == 'D'){
            while(grid [row][column] != 0 && column < 6 && row < 5){
                column++;
                if (column == 6) {
                    column = 1;
                    row++;
                }
            }
            grid [row][column] = 'D';
            positionGrid [row][column] = incrementer;
           
            column++;
            if (column == 6) {
                column = 1;
                row++;
            }
            
        }
        if( state[incrementer] == 'E'){
            while(grid [row][column] != 0 && column < 6 && row < 5){
                column++;
                if (column == 6) {
                    column = 1;
                    row++;
                }
            }
            grid [row][column] = 'E';
            positionGrid [row][column] = incrementer;
            positionERow[eTracker] = row;
            positionEColumn[eTracker] = column;
            column++;
            if (column == 6) {
                column = 1;
                row++;
            }
            eTracker++;
            
        }
        

    }

    
    row = 0;
    column = 0;
    if (option != 0) {
        emptySpot[0].epos = positionGrid[positionERow[0]][positionEColumn[0]];
        emptySpot[0].left = grid[positionERow[0]][positionEColumn[0]-1];
        emptySpot[0].pos[0] = positionGrid[positionERow[0]][positionEColumn[0]-1];
        
        emptySpot[0].top = grid [positionERow[0]-1][positionEColumn[0]];
        emptySpot[0].pos[1] = positionGrid[positionERow[0]-1][positionEColumn[0]];
        
        emptySpot[0].right = grid[positionERow[0]][positionEColumn[0]+1];
        emptySpot[0].pos[2] = positionGrid[positionERow[0]][positionEColumn[0]+1];
        
        emptySpot[0].bottom = grid[positionERow[0]+1][positionEColumn[0]];
        emptySpot[0].pos[3] = positionGrid[positionERow[0]+1][positionEColumn[0]];
        
        
        emptySpot[1].epos = positionGrid[positionERow[1]][positionEColumn[1]];
        emptySpot[1].left = grid[positionERow[1]][positionEColumn[1]-1];
        emptySpot[1].pos[0] = positionGrid[positionERow[1]][positionEColumn[1]-1];
        
        emptySpot[1].top = grid [positionERow[1]-1][positionEColumn[1]];
        emptySpot[1].pos[1] = positionGrid[positionERow[1]-1][positionEColumn[1]];
        
        emptySpot[1].right = grid[positionERow[1]][positionEColumn[1]+1];
        emptySpot[1].pos[2] = positionGrid[positionERow[1]][positionEColumn[1]+1];
        
        emptySpot[1].bottom = grid[positionERow[1]+1][positionEColumn[1]];
        emptySpot[1].pos[3] = positionGrid[positionERow[1]+1][positionEColumn[1]];
    }
    if (option == 0){
        for (positionRow = 1; positionRow<5; positionRow++) {
            for (positionColumn = 1; positionColumn < 6; positionColumn++) {
                if (row%2 != 1 && column%2 != 1) {
                    
                    printf(" %s| ", KWHT);
                    
                }
                if (grid[positionRow][positionColumn] == 'B') {
		            printf(" %s%c ", KBLU, grid[positionRow][positionColumn]);
		        }
		        if (grid[positionRow][positionColumn] == 'E') {
                    printf(" %s%c ", KWHT, grid[positionRow][positionColumn]);
		        }
		        if (grid[positionRow][positionColumn] == 'D') {
                    printf(" %s%c ", KGRN, grid[positionRow][positionColumn]);
                }
                if (grid[positionRow][positionColumn] == 'A') {
                    printf("  %s%c  ", KRED, grid[positionRow][positionColumn]);
		            row++;
		        }
		        if (grid[positionRow][positionColumn] == 'C') {
                    printf("  %s%c  ", KYEL, grid[positionRow][positionColumn]);
		            column++;
                }
            }
            printf("\n%s--------------------------------\n", KWHT);
        }
    }
    printf(RESET);
}

MOVES *getAllPossible(char *pstr){
    int counter = 0;
    int i = 0;
    MOVES *store;
    store = malloc(sizeof(MOVES));
    store->size = 0;
    
    printPuzzle(pstr, 1);
    
    store->m = malloc(sizeof(*store[0].m) * 7);
/*--------------------D--------------------*/
    if (emptySpot[0].left == 'D') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],0,0, positionERow[0], positionEColumn[0] - 1,0,0);
        counter++;
    }
    if (emptySpot[0].top == 'D') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter],positionERow[0],positionEColumn[0],0,0, positionERow[0] - 1, positionEColumn[0],0,0);
        counter++;
    }
    if (emptySpot[0].right == 'D') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],0,0, positionERow[0], positionEColumn[0] + 1,0,0);
        counter++;
    }
    if (emptySpot[0].bottom == 'D') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],0,0, positionERow[0]+1, positionEColumn[0],0,0);
        counter++;
    }
   
/*--------------------A--------------------*/
    if (emptySpot[0].left == 'A' ) {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],0,0, positionERow[0], positionEColumn[0]-2,0,0);
        counter++;
    }
 
    if (emptySpot[0].top == 'A' && ((positionEColumn[0] + 1) == positionEColumn[1])) {
        if (emptySpot[1].top == 'A' && (positionERow[0] == positionERow[1])) {
            if (grid[positionERow[0] - 1][positionEColumn[0] - 1] != 'A' || grid[positionERow[1] - 1][positionEColumn[1] + 1] != 'A'  )  {
                store->m[counter] = malloc(sizeof(store->m)*13);
                strcpy(store->m[counter],pstr);
                cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],positionERow[1],positionEColumn[1], positionERow[0]-1, positionEColumn[0],positionERow[1]-1,positionEColumn[1]);
                counter++;
            }
        }
        
        
    }
    if (emptySpot[0].right == 'A') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],0,0, positionERow[0], positionEColumn[0]+2,0,0);
        counter++;
    }

    if (emptySpot[0].bottom == 'A' && ((positionEColumn[0] + 1) == positionEColumn[1])) {
        if (emptySpot[1].bottom == 'A' && (positionERow[0] == positionERow[1])) {
            if (grid[positionERow[0] + 1][positionEColumn[0] - 1] != 'A' || grid[positionERow[1] + 1][positionEColumn[1] + 1] != 'A'  ){
                store->m[counter] = malloc(sizeof(store->m)*13);
                strcpy(store->m[counter],pstr);
                cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],positionERow[1],positionEColumn[1], positionERow[0]+1, positionEColumn[0],positionERow[1]+1,positionEColumn[1]);
                counter++;
            }
        }
        
    }
    /*Option 0 is C on the bottom and 2 the C on top.
     3 is empty on bottom swap with B
     4 is empty on right swap with A
     5 is two empty with A
     6 is E on top with b
     7 is second E with B on top
     8 is second E with B on bottom
     */
/*--------------------B--------------------*/
    if (emptySpot[0].left == 'B') {
        if ( emptySpot[1].left == 'B') {
            store->m[counter] = malloc(sizeof(store->m)*13);
            strcpy(store->m[counter],pstr);
            cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],positionERow[1],positionEColumn[1], positionERow[0], positionEColumn[0]-1,positionERow[1],positionEColumn[1]-1);
            counter++;
        }
        
    }
  
    if (emptySpot[0].top == 'B') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],0,0, positionERow[0]-2, positionEColumn[0],0,0);
        counter++;

        
    }
    if (emptySpot[0].right == 'B') {
        if ( emptySpot[1].right == 'B') {
            store->m[counter] = malloc(sizeof(store->m)*13);
            strcpy(store->m[counter],pstr);
            cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],positionERow[1],positionEColumn[1], positionERow[0], positionEColumn[0]+1,positionERow[1],positionEColumn[1]+1);
            counter++;
            
        }
        
    }

    if (emptySpot[0].bottom == 'B') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],0,0, positionERow[0]+2, positionEColumn[0],0,0);
        counter++;
     
        
    }
    
/*--------------------C--------------------*/
    if (emptySpot[0].left == 'C') {
        if ( emptySpot[1].left == 'C') {
            store->m[counter] = malloc(sizeof(store->m)*13);
            strcpy(store->m[counter],pstr);
            cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],positionERow[1],positionEColumn[1], positionERow[0], positionEColumn[0]-2,positionERow[1],positionEColumn[1]-2);
            counter++;
        }
        
    }
    
    if (emptySpot[0].top == 'C') {
        
        if (emptySpot[1].top == 'C') {
            store->m[counter] = malloc(sizeof(store->m)*13);
            strcpy(store->m[counter],pstr);
            cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],positionERow[1],positionEColumn[1], positionERow[0]-2, positionEColumn[0],positionERow[1]-2,positionEColumn[1]);
            counter++;
        }
        
        
    }
    if (emptySpot[0].right == 'C') {
        
        if ( emptySpot[1].right == 'C') {
            store->m[counter] = malloc(sizeof(store->m)*13);
            strcpy(store->m[counter],pstr);
            cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],positionERow[1],positionEColumn[1], positionERow[0], positionEColumn[0]+2,positionERow[1],positionEColumn[1]+2);
            i = emptySpot[1].epos;
            counter++;
        }
       
    }
    
    if (emptySpot[0].bottom == 'C') {
        if (emptySpot[1].bottom == 'C') {
            store->m[counter] = malloc(sizeof(store->m)*13);
            strcpy(store->m[counter],pstr);
            cswapPositions(store->m[counter], positionERow[0], positionEColumn[0],positionERow[1],positionEColumn[1], positionERow[0]+2, positionEColumn[0],positionERow[1]+2,positionEColumn[1]);
            
            counter++;
        }
        
    }
    
/*
----------------------Second Empty-------------------------
-----------------------------------------------------------
     
*/
    /*--------------------D--------------------*/
    
    if (emptySpot[1].left == 'D') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[1], positionEColumn[1],0,0, positionERow[1], positionEColumn[1] - 1,0,0);
        counter++;
    }
    if (emptySpot[1].top == 'D') {
        
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[1], positionEColumn[1],0,0, positionERow[1]-1, positionEColumn[1],0,0);
        counter++;
    }
    if (emptySpot[1].right == 'D') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[1], positionEColumn[1],0,0, positionERow[1], positionEColumn[1] + 1,0,0);
        counter++;
    }
    if (emptySpot[1].bottom == 'D') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[1], positionEColumn[1],0,0, positionERow[1]+1, positionEColumn[1],0,0);
        counter++;
    }
    
    /*--------------------A--------------------*/
    if (emptySpot[1].left == 'A') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[1], positionEColumn[1],0,0, positionERow[1], positionEColumn[1]-2,0,0);
        counter++;
        
    }
    
    if (emptySpot[1].right == 'A') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[1], positionEColumn[1],0,0, positionERow[1], positionEColumn[1]+2,0,0);
        counter++;
    }
    /*Option 0 is C on the bottom and 2 the C on top.
     3 is empty on bottom swap with B
     4 is empty on right swap with A
     5 is two empty with A
     6 is E on top with b
     7 is second E with B on top
     8 is second E with B on bottom
     */
    /*--------------------B--------------------*/
    
    if (emptySpot[1].top == 'B') {
        
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[1], positionEColumn[1],0,0, positionERow[1]-2, positionEColumn[1],0,0);
        counter++;
         
        
    }
    
    if (emptySpot[1].bottom == 'B') {
        store->m[counter] = malloc(sizeof(store->m)*13);
        strcpy(store->m[counter],pstr);
        cswapPositions(store->m[counter], positionERow[1], positionEColumn[1],0,0, positionERow[1]+2, positionEColumn[1],0,0);
        counter++;
        
    }
    
    store->size = counter;
    
    return store;
}
