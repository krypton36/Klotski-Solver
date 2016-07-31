#include "p1.h"

unsigned int hash(HASHTABLE *ht, char *s){
    int slength = strlen(s);
    unsigned int hash  = 1;
    int i;
    for (i = 0; i < slength; i++) {
        hash *= s[i];
    }
    return (unsigned int) (hash%ht->size);
}
void setTableSize(unsigned int tbs){
    tableSize = tbs;
}
HASHTABLE *createHashTable(unsigned long size){
    HASHTABLE *new_table;
    int i;
    
    
    if (size<1) return NULL;
    
    if ((new_table = malloc(sizeof(HASHTABLE))) == NULL) {
        return NULL;
    }
    
    if ((new_table->table = malloc(sizeof(LINKEDLIST *) * size)) == NULL) {
        return NULL;
    }
    
    for(i=0; i<size; i++) new_table->table[i] = NULL;
    
    new_table->size = size;
    setTableSize(size);
    
    return new_table;
}

LINKEDLIST *lookup(HASHTABLE *hashtable, char *str){
    LINKEDLIST *list;
    unsigned int hashval = hash(hashtable, str);
    
    /* Go to the correct list based on the hash value and see if str is
     * in the list.  If it is, return return a pointer to the list element.
     * If it isn't, the item isn't in the table, so return NULL.
     */
    for(list = hashtable->table[hashval]; list != NULL; list = list->next) {
        if (strcmp(str, list->str) == 0) return list;
    }
    return NULL;
}

int addToHashTable(HASHTABLE *hashtable, char *str){
    LINKEDLIST *new_list;
    LINKEDLIST *current_list;
    unsigned int hashval = hash(hashtable, str);
    
    if ((new_list = malloc(sizeof(LINKEDLIST))) == NULL) return 1;
    
    current_list = lookup(hashtable, str);
    
    /* item already exists, don't insert it again. */
    if (current_list != NULL) return 2;

    new_list->str = strdup(str);
    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;
    
    return 0;
}
void freeTable(HASHTABLE *hashtable){
    int i;
    LINKEDLIST *list, *temp;
    
    if (hashtable==NULL) return;
    
    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            free(temp->str);
            free(temp);
        }
    }
    
    free(hashtable->table);
    free(hashtable);
}
