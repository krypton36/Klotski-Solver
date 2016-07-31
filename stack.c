#include "p1.h"

/*Simple Stack to use for the printing
  of the moves to get to the final state.
 Then loop in p1.c will backtrace and add 
 to the stack and then pop the off when 
 printing them.
*/
LINKEDLIST *Stackhead;
int stackSize = 0;


void addStack(unsigned int val) {
    LINKEDLIST *ptr;
    ptr = malloc(sizeof(LINKEDLIST));
    ptr->val = val;
    ptr->next = NULL;
    
    if (Stackhead == NULL) {
        Stackhead = ptr;
        stackSize++;
    }
    else{
        ptr->next = Stackhead;
        Stackhead = ptr;
        stackSize ++;
    }
}
unsigned int popStack(){
    LINKEDLIST *ptr;
    
    if (stackSize== 0) {
        return -1;
    }
    ptr = Stackhead;
    Stackhead = ptr->next;
    
    stackSize--;
    
    return ptr->val;
}
