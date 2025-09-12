#ifndef T_LIST_PRIVATE
#define T_LIST_PRIVATE

#include "Tlist.h"
#include <stdarg.h>

struct Node{
    void *val;
    Node nextNode;
};

Node newNode(void *val, size_t size, Type type);
void print(List this);
void push(List this, ...);
int len(List this);
void destroyList(List this);
void *pop(List this);
void *get(List this, int index);
void set(List this, int index, ...);
void delete(List this, int index);
void insert(List this, int index, ...);
void *pick(List this, int index);
void foreach(List this, void(*function)(void*));

#endif
