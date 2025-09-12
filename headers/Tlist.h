#ifndef T_LIST
#define T_LIST

#include <stddef.h>

typedef enum Type{
    T,
    INT,
    STRING,
    FLOAT,
    DOUBLE
} Type;

typedef struct Lista *List;
typedef struct Node *Node;
struct Lista{
    /* List state */
    Node head;     
    Type type;     
    size_t size;   

    /* Methods */
    void (*push)(List, ...);
    void *(*pop)(List);
    void (*print)(List);
    int (*len)(List);
    void (*free)(List);
    void *(*get)(List, int);
    void (*set)(List, int, ...);
    void (*remove)(List, int);
    void (*insert)(List, int, ...);
    void *(*pick)(List, int);
    void(*foreach)(List, void(*function)(void*));
};

List newList(Type type);

#endif
