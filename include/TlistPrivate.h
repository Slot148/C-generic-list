#ifndef T_LIST_PRIVATE
#define T_LIST_PRIVATE

#include "Tlist.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * @struct Node
 * @brief Represents a node in the singly linked list.
 * @private
 */
struct Node{
    void *_val;      /**< Pointer to the data stored in the node. */
    Node _nextNode;  /**< Pointer to the next node in the list. */
};

/**
 * @struct TIterator
 * @brief Represents an iterator for a `List`.
 * @private
 */
struct TIterator{
    Node _current;                          /**< Pointer to the current node in the iteration. */
    List _list;                             /**< Pointer to the list being iterated. */
    int _index;                             /**< The index of the current element. */
    void* (*next)(struct TIterator*);       /**< Method to get the next element. */
    bool (*hasNext)(struct TIterator*);     /**< Method to check if there is a next element. */
    void (*free)(struct TIterator*);        /**< Method to free the iterator structure. */
};

/**
 * @brief Creates a new list node.
 * @private
 * @param val Pointer to the value to be stored.
 * @param size Size of the value type.
 * @param type The type of data being stored.
 * @return The newly created node.
 */
Node newNode(void *val, size_t size, Type type);

/**
 * @brief Implementation for the `print` method. Prints the list to stdout.
 * @private
 */
void print(List this);

/**
 * @brief Implementation for the `push` method. Adds an element to the end of the list.
 * @private
 */
void push(List this, ...);

/**
 * @brief Implementation for the `len` method. Returns the number of elements.
 * @private
 */
int len(List this);

/**
 * @brief Implementation for the `free` method. Frees all nodes and their data.
 * @private
 */
void destroyList(List this);

/**
 * @brief Implementation for the `pop` method. Removes and returns the first element.
 * @private
 */
void *pop(List this);

/** @private */
void *get(List this, int index);
/** @private */
void set(List this, int index, ...);
/** @private */
void delete(List this, int index);
/** @private */
void insert(List this, int index, ...);
/** @private */
void *pick(List this, int index);
/** @private */
void foreach(List this, void(*function)(void*));

/**
 * @brief Implementation for the iterator's `next` method. Returns the next element.
 * @private
 */
void* next(TIterator iterator);

/**
 * @brief Implementation for the iterator's `hasNext` method. Checks for more elements.
 * @private
 */
bool hasNext(TIterator iterator);

/**
 * @brief Implementation for the iterator's `free` method. Frees the iterator.
 * @private
 */
void freeIterator(TIterator iterator);

#endif
