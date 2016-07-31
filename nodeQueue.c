#include "p1.h"

NODELIST *nodeFirst;
NODELIST *nodeLast;
int nlSize = 0;


void addNodeFirst(PATH_NODE * val) {
    NODELIST *ptr;
    ptr = malloc(sizeof(NODELIST));
    ptr->val = malloc(sizeof(PATH_NODE));
    ptr->val->key_value = val->key_value;
    ptr->next = NULL;
    
    if (nodeFirst == NULL) {
        nodeFirst = nodeLast = ptr;
        nlSize++;
    }
    else{
        ptr->next = nodeFirst;
        nodeFirst = ptr;
        nlSize++;
    }
}
void pushNodeLast(PATH_NODE * val) {
    NODELIST *ptr;
    
    ptr = malloc(sizeof(NODELIST));
    ptr->val = malloc(sizeof(PATH_NODE));
    ptr->val->key_value = val->key_value;
    
    if (nodeFirst == NULL) {
        addNodeFirst(val);
    }
    else{
        nodeLast->next = ptr;
        nodeLast = ptr;
        ptr->next = NULL;
        nlSize++;
    }
    
}
void addPreviousNode(PATH_NODE * val){
    nodeLast->val->previousNode = malloc(sizeof(PATH_NODE));
    *nodeLast->val->previousNode = *val;

}
PATH_NODE * popNode(){
    NODELIST *ptr;
    
    if (nlSize == 0) {
        return NULL;
    }
    ptr = nodeFirst;
    nodeFirst = ptr->next;
    
    nlSize--;
    
    return ptr->val;
}
int getnlSize(){
    return nlSize;
}
void traverse_list() {
    NODELIST * current = nodeFirst;
    
    if (nlSize > 0) {
        while (current != NULL) {
            printf("%X\n", current->val->key_value);
            current = current->next;
        }
    }
}
    