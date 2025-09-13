/**
 * @file Tlist.c
 * @brief Implementation of a generic, type-aware singly linked list in C.
 *
 * This module provides a generic list capable of storing elements of different
 * types (int, float, double, C-strings, or generic pointers) determined at
 * list creation time.
 *
 * For primitive types (INT, FLOAT, DOUBLE) and STRING, the list manages memory
 * internally by copying values. For the generic pointer type (T), the list
 * only stores the pointer itself, and the caller is responsible for managing
 * the memory of the pointed-to data.
 */

#include "Tlist.h"
#include "TlistPrivate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @copydoc newList */
List newList(Type type){
    List this = (List)malloc(sizeof(struct Lista));
    this->head = NULL;
    this->type = type;

    // list methods
    this->print = print;
    this->free = destroyList;
    this->push = push;
    this->pop = pop;
    this->len = len;
    this->get = get;
    this->set = set;
    this->remove = delete;
    this->insert = insert;
    this->pick = pick;
    this->foreach = foreach;

    switch(type){
        case INT:
            this->size = sizeof(int);
            break;
        case STRING:
            this->size = sizeof(char *);
            break;
        case DOUBLE:
            this->size = sizeof(double);
            break;
        case FLOAT:
            this->size = sizeof(float);
            break;
        case T:
            this->size = sizeof(void *);
            break;
    }

    return this;
}

/**
 * @brief Creates a new list node and allocates memory for its value.
 *
 * For `INT`, `FLOAT`, and `DOUBLE`, it allocates `size` bytes and copies the value.
 * For `STRING`, it allocates memory for a new string and copies the content.
 * For `T`, it does not allocate memory for the value but stores the pointer `val` directly.
 *
 * @param val A pointer to the value to be stored in the node.
 * @param size The size of the data type (for value types).
 * @param type The `Type` of the data.
 * @return A pointer to the newly created `Node`.
 * @private
 */
Node newNode(void *val, size_t size, Type type){
    Node node = (Node)malloc(sizeof(struct Node));    
    if (type == STRING) {
        node->val = malloc(strlen((char *)val) + 1);
        strcpy((char *)node->val, (char *)val);
    }
    else if (type == T) {
        node->val = val;
    }
    else {
        node->val = malloc(size);
        memcpy(node->val, val, size);
    }   
    node->nextNode = NULL;
    return node;
}

/**
 * @brief Prints the contents of the list to standard output.
 * @param this A pointer to the list.
 * @private
 */
void print(List this){
    printf("[");
    for (Node current = this->head; current != NULL; current = current->nextNode){
        switch (this->type){
            case INT:
                printf("%d", *(int *)current->val);
                break;
            case STRING:
                printf("\"%s\"", (char *)current->val);
                break;
            case DOUBLE:
                printf("%.2f", *(double *)current->val);
                break;
            case FLOAT:
                printf("%.2f", *(float *)current->val);
                break;
            case T:
                printf("%p", current->val);
                break;
        }
        if (current->nextNode != NULL){
            printf(", ");
        }
    }
    printf("]");
    printf("\n");
}

/**
 * @brief Frees all the nodes in the list and the data they contain.
 *
 * It iterates through the list, freeing each node. For all types except `T`,
 * it also frees the memory allocated for the node's value (`val`). For type `T`,
 * it is the caller's responsibility to free the pointed-to data before or after
 * calling this function (e.g., using `foreach`). This function does NOT free
 * the `List` struct itself.
 * @param this A pointer to the list.
 */
void destroyList(List this){
    Node current = this->head;
    while (current != NULL){
        Node temp = current;
        current = temp->nextNode;
        if(this->type != T) free(temp->val);
        free(temp);
    }
    this->head = NULL;
}

/**
 * @brief Helper function to add a node to the end of the list.
 * @param this A pointer to the list.
 * @param node The node to be added.
 * @private
 */
void underPush(List this, Node node){
    if (this->head == NULL){
        this->head = node;
    }
    else{
        Node current = this->head;
        while (current->nextNode != NULL){
            current = current->nextNode;
        }
        current->nextNode = node;
    }
}

/**
 * @brief Adds a new element to the end of the list.
 *
 * This is a variadic function. The type of the argument after `this` must
 * match the list's `Type`.
 * - For `INT`: `int`
 * - For `FLOAT`, `DOUBLE`: `double` (due to default argument promotion)
 * - For `STRING`: `char*`
 * - For `T`: `void*`
 * @param this A pointer to the list.
 */
void push(List this, ...){
    va_list args;
    va_start(args, this);
    switch (this->type){
        case INT:{
            int val = va_arg(args, int);
            underPush(this, newNode(&val, this->size, this->type));
            break;
        }
        case STRING:{
            char *str = va_arg(args, char *);
            underPush(this, newNode(str, this->size, this->type));
            break;
        }
        case DOUBLE:{
            double dbl = va_arg(args, double);
            underPush(this, newNode(&dbl, this->size, this->type));
            break;
        }
        case FLOAT:{
            float flt = (float)va_arg(args, double);
            underPush(this, newNode(&flt, this->size, this->type));
            break;
        }
        default:{
            void *unkown = va_arg(args, void *);
            underPush(this, newNode(unkown, this->size, this->type));
            break;
        }
    }
    va_end(args);
}

/**
 * @brief Calculates and returns the number of elements in the list.
 * @param this A pointer to the list.
 * @return The number of elements.
 */
int len(List this){
    int len = 0;
    for (Node current = this->head; current != NULL; current = current->nextNode){
        len++;
    }
    return len;
}

/**
 * @brief Removes the first element (head) of the list and returns its value.
 *
 * The caller takes ownership of the returned pointer and is responsible for
 * freeing it. For type `T`, the returned pointer is the one that was originally
 * inserted. For other types, it's a pointer to a heap-allocated copy.
 *
 * @param this A pointer to the list.
 * @return A pointer to the value of the removed element, or `NULL` if the list is empty.
 */
void *pop(List this){
    if (this->head == NULL){
        return NULL;
    }else {
        Node current = this->head;
        this->head = current->nextNode;
        void *val = current->val;
        free(current);
        return val;
    }
}

/**
 * @brief Retrieves a pointer to the element at a specific index.
 *
 * This function provides direct but read-only access to the internal data.
 * The returned pointer is owned by the list and should not be freed by the caller.
 * Its validity is only guaranteed until the next list-modifying operation.
 * For `INT`, `FLOAT`, `DOUBLE`, this will be a pointer to the heap-allocated value.
 * For `STRING`, a pointer to the internal string copy.
 * For `T`, the original `void*` that was inserted.
 *
 * @param this A pointer to the list.
 * @param index The zero-based index of the element to retrieve.
 * @return A pointer to the element's value, or `NULL` if the index is out of bounds.
 */
void *get(List this, int index){
    int x = 0;
    Node current = this->head;
    while (current != NULL){
        if (x == index){
            return current->val;
        }
        current = current->nextNode;
        x++;
    } 
    return NULL;
}

/**
 * @brief Updates the value of an element at a specific index.
 *
 * This is a variadic function. The argument after `index` must match the list's `Type`.
 * For `STRING`, the old string is freed and a new one is allocated and copied.
 * For `T`, the pointer is simply replaced.
 *
 * @param this A pointer to the list.
 * @param index The zero-based index of the element to update.
 */
void set(List this, int index, ...){
    va_list args;
    va_start(args, index);
    Node current = this->head;
    int x = 0;
    while (current != NULL){
        if (x == index)
            switch (this->type){
                case INT:{
                    int val = va_arg(args, int);
                    memcpy(current->val, &val, this->size);
                    break;
                }
                case FLOAT:{
                    float flt = (float)va_arg(args, double);
                    memcpy(current->val, &flt, this->size);
                    break;
                }
                case DOUBLE:{
                    double dbl = va_arg(args, double);
                    memcpy(current->val, &dbl, this->size);
                    break;
                }
                case STRING:{
                    char *chr = va_arg(args, char *);
                    free(current->val);
                    current->val = malloc(strlen(chr) + 1);
                    strcpy((char *)current->val, chr);
                    break;
                }
                case T:{
                    void *nil = va_arg(args, void *);
                    current->val = nil;
                    break;
                }
            }
        current = current->nextNode;
        x++;
    }
    va_end(args);
}

/**
 * @brief Deletes the element at a specific index.
 *
 * This function removes the node and frees the associated memory for its value
 * (unless the list type is `T`).
 * @param this A pointer to the list.
 * @param index The zero-based index of the element to delete.
 */
void delete(List this, int index){
    if (index == 0) {
        void* v = this->pop(this);
        if (this->type != T) free(v);
        return;
    }
    Node current = this->head;
    int x = 0;
    while (current != NULL){
        if (index - 1 == x && index != 0){
            Node temp = current->nextNode;
            current->nextNode = temp->nextNode;
            if(this->type != T) free(temp->val);
            free(temp);
        }
        current = current->nextNode;
        x++;
    }
}

/**
 * @brief Helper function to insert a node at a specific index.
 * @param this A pointer to the list.
 * @param index The zero-based index where the node should be inserted.
 * @param node The node to insert.
 * @private
 */
void underInsert(List this, int index, Node node){
    Node current = this->head;
    int x = 0;
    if (index == 0){
        this->head = node;
        node->nextNode = current;
        return;
    }
    while (current != NULL){
        if (x == index - 1){
            Node temp = current->nextNode;
            current->nextNode = node;
            node->nextNode = temp;
        }
        current = current->nextNode;
        x++;
    }
}

/**
 * @brief Inserts a new element at a specific index.
 *
 * This is a variadic function. The argument after `index` must match the list's `Type`.
 * @param this A pointer to the list.
 * @param index The zero-based index at which to insert the new element.
 */
void insert(List this, int index, ...){
    va_list args;
    va_start(args, index);

    switch (this->type){
        case INT:{
            int val = va_arg(args, int);
            underInsert(this, index, newNode(&val, this->size, this->type));
            break;
        }
        case STRING:{
            char *str = va_arg(args, char *);
            underInsert(this, index, newNode(str, this->size, this->type));
            break;
        }
        case DOUBLE:{
            double dbl = va_arg(args, double);
            underInsert(this, index, newNode(&dbl, this->size, this->type));
            break;
        }
        case FLOAT:{
            float flt = (float)va_arg(args, double);
            underInsert(this, index, newNode(&flt, this->size, this->type));
            break;
        }
        default:{
            void *unkown = va_arg(args, void *);
            underInsert(this, index, newNode(unkown, this->size, this->type));
            break;
        }
    }

    va_end(args);
}

/**
 * @brief Removes and returns the element at a specific index.
 *
 * The caller takes ownership of the returned pointer and is responsible for
 * freeing it. For type `T`, the returned pointer is the one that was originally
 * inserted. For other types, it's a pointer to a heap-allocated copy.
 *
 * @param this A pointer to the list.
 * @param index The zero-based index of the element to remove.
 * @return A pointer to the value of the removed element, or `NULL` if the index is out of bounds.
 */
void *pick(List this, int index){
    if(index == 0){
        return this->pop(this);
    }else if (this->head == NULL){
        return NULL;
    }else {
        Node current = this->head;
        int x = 0;
        while (current != NULL){
            if (x == index - 1 && current->nextNode != NULL){
                Node temp = current->nextNode;
                current->nextNode = temp->nextNode;
                void *n = temp->val;
                free(temp);
                return n;
            }
            current = current->nextNode;
            x++;
        } 
    }
    return NULL;
}

/**
 * @brief Applies a given function to each element in the list.
 *
 * @param this A pointer to the list.
 * @param function A function pointer that takes a `void*` (the element's data) and returns `void`.
 */
void foreach(List this, void(*function)(void*)){
    for(Node current = this->head; current != NULL; current = current->nextNode){
        function(current->val);
    }
}
