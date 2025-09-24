#include "Tlist.h"
#include "TlistPrivate.h"

TIterator newIterator(List list){
    TIterator iterator = malloc(sizeof(struct TIterator));
    if(iterator == NULL) {
        fprintf(stderr, "Error in newIterator(): Failed to allocate memory for the new iterator.\n");
        exit(EXIT_FAILURE);
    }
    iterator->_list = list;
    iterator->_current = list->_head;
    iterator->_index = 0;
    iterator->next = next;
    iterator->hasNext = hasNext;
    iterator->free = freeIterator;
    return iterator;
}

void* next(TIterator iterator){
    if (iterator == NULL || iterator->_current == NULL) {
        fprintf(stderr, "Error in next(): No more elements to iterate or invalid iterator.\n");
        return NULL;
    }
    void* val = iterator->_current->_val;
    iterator->_index++;
    iterator->_current = iterator->_current->_nextNode;
    return val;
}

bool hasNext(TIterator iterator){
    if (iterator == NULL) {
        return false;
    }
    return iterator->_current != NULL;
}

void freeIterator(TIterator iterator){
    free(iterator);
}