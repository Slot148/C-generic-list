/**
 * @file Tlist.c
 * @brief Implementation of a generic singly linked list in C.
 *
 * This module provides a generic list capable of storing elements of different
 * types (int, float, double, C-strings, or generic pointers) determined at
 * list creation time. The list stores values by value for numeric types and
 * duplicates C-strings. See function documentation for ownership semantics.
 */

#include "Tlist.h"
#include "TlistPrivate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int len(List this){
    int len = 0;
    for (Node current = this->head; current != NULL; current = current->nextNode){
        len++;
    }
    return len;
}

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

void foreach(List this, void(*function)(void*)){
    for(Node current = this->head; current != NULL; current = current->nextNode){
        function(current->val);
    }
}
