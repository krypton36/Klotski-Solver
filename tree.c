#include "p1.h"
/*
 A (Two Block Horizontal 4) = 10, B (Two Block Vertical 1) = 010, C (Four Block Square 1) = 011
 D (Single Block 4) = 11, E (Single Block Empty 2) = 00.
 */

/*
 Since we know that the language will not change
 and the values provided for the blocks are always
 constant, we created a tree from that values. This
 makes the efficiency big Theta(1);
 */
void buildTree(){
    huffTree[3].letter = 'E';
    huffTree[3].key_value = 0;
    
    huffTree[7].letter = 'B';
    huffTree[7].key_value = 0;
    
    huffTree[8].letter = 'C';
    huffTree[8].key_value = 1;
    
    huffTree[5].letter = 'A';
    huffTree[5].key_value = 0;
    
    huffTree[6].letter = 'D';
    huffTree[6].key_value = 1;

    huffTree[0].left = &huffTree[1];
    huffTree[0].right = &huffTree[2];
    
    huffTree[1].left = &huffTree[3];
    huffTree[1].right = &huffTree[4];
    huffTree[1].key_value = 0;
    
    huffTree[2].left = &huffTree[5];
    huffTree[2].right = &huffTree[6];
    huffTree[2].key_value = 1;
    
    huffTree[4].left = &huffTree[7];
    huffTree[4].right = &huffTree[8];
    
}
/*
 Decode function allows the decoding of a 26 bit value.
 It starts from the most left bit and iterated to the right.
 Each time is finds a letter, if resets the iterator back to
 the top of the tree and prints the letter. The efficiency of
 the iteration to decode is big Theta(1), since there is no
 variation in the input size or tree size.
 */
char *decode(FBYTE val){
    char *decodedString;
    decodedString = (char *) malloc (sizeof(char) * 13);
    int dcounter, letterCounter = 0;
    buildTree();
    struct node *iterator;
    iterator = huffTree;
   
   for (dcounter = 0; dcounter < 26; dcounter++) {
        if ((val & (COMPARE >> dcounter)) == (COMPARE >> dcounter)) {
            iterator = iterator->right;
            
            if(iterator->letter != 0){
                decodedString[letterCounter++] = iterator->letter;
                iterator = huffTree;
            }
        }
        else{
            iterator = iterator->left;
            if(iterator->letter != 0){
                decodedString[letterCounter++] = iterator->letter;
                iterator = huffTree;
            }
        }
    }
    decodedString[12] = 0;
    return decodedString;
}

FBYTE encode(char *dString){
    int counter;
    FBYTE encodedVal = 0;
    
    for (counter = 0; counter < 12; counter++) {
        
        if (dString[counter] == 'A'){
            encodedVal <<= 2;
            encodedVal += 2;
        }
        if (dString[counter] == 'B'){
            encodedVal <<= 3;
            encodedVal += 2;
        }
        if (dString[counter] == 'C'){
            
            encodedVal <<= 3;
            encodedVal += 3;
        }
        if (dString[counter] == 'D'){
            encodedVal <<= 2;
            encodedVal += 3;
        }
        if (dString[counter] == 'E'){
            encodedVal <<= 2;
        }
    }
    return encodedVal;
}