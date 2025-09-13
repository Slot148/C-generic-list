#include "Tlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa {
    char nome[30];
    int idade;
} Pessoa;

Pessoa* newPessoa(const char* nome, int idade){
    Pessoa* p = (Pessoa*)malloc(sizeof(Pessoa));
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';
    p->idade = idade;
    return p;
}

void printPessoa(void* data){
    Pessoa* p = (Pessoa*)data;
    printf("Pessoa{ nome=%s, idade=%d }\n", p->nome, p->idade);
}

void freePessoa(void* data){
    free(data);
}

void testInts() {
    printf("\n=== Teste INT ===\n");
    List l = newList(INT);
    l->push(l, 10);
    l->push(l, 20);
    l->push(l, 30);
    l->print(l);

    printf("len=%d\n", l->len(l));
    printf("get(1)=%d\n", *(int*)l->get(l,1));

    l->set(l,1, 99);
    l->print(l);

    l->insert(l,1, 77);
    l->print(l);

    void* v = l->pop(l);
    printf("pop=%d\n", *(int*)v);
    free(v);

    v = l->pick(l,1);
    printf("pick=%d\n", *(int*)v);
    free(v);

    l->print(l);
    l->free(l);
    free(l);
}

void testStrings() {
    printf("\n=== Teste STRING ===\n");
    List l = newList(STRING);
    l->push(l, "Alice");
    l->push(l, "Bob");
    l->push(l, "Charlie");
    l->print(l);

    l->set(l,1,"Bobby");
    l->print(l);

    l->insert(l,1,"Inserted");
    l->print(l);

    void* v = l->pop(l);
    printf("pop=%s\n", (char*)v);
    free(v);

    v = l->pick(l,1);
    printf("pick=%s\n", (char*)v);
    free(v);

    l->print(l);
    l->free(l);
    free(l);
}

void testFloats() {
    printf("\n=== Teste FLOAT ===\n");
    List l = newList(FLOAT);
    l->push(l, 1.5);
    l->push(l, 2.25);
    l->push(l, 3.75);
    l->print(l);

    l->set(l,1, 9.99);
    l->print(l);

    l->insert(l,1, 7.77);
    l->print(l);

    void* v = l->pop(l);
    printf("pop=%.2f\n", *(float*)v);
    free(v);

    v = l->pick(l,1);
    printf("pick=%.2f\n", *(float*)v);
    free(v);

    l->print(l);
    l->free(l);
    free(l);
}

void testDoubles() {
    printf("\n=== Teste DOUBLE ===\n");
    List l = newList(DOUBLE);
    l->push(l, 1.111);
    l->push(l, 2.222);
    l->push(l, 3.333);
    l->print(l);

    l->set(l,1, 9.999);
    l->print(l);

    l->insert(l,1, 7.777);
    l->print(l);

    void* v = l->pop(l);
    printf("pop=%.2f\n", *(double*)v);
    free(v);

    v = l->pick(l,1);
    printf("pick=%.2f\n", *(double*)v);
    free(v);

    l->print(l);
    l->free(l);
    free(l);
}

void testPessoa() {
    printf("\n=== Teste T (struct Pessoa*) ===\n");
    List l = newList(T);
    Pessoa* p1 = newPessoa("Alice", 30);
    Pessoa* p2 = newPessoa("Bob", 25);
    Pessoa* p3 = newPessoa("Charlie", 35);

    l->push(l, p1);
    l->push(l, p2);
    l->push(l, p3);

    l->print(l); // mostra só endereços
    l->foreach(l, printPessoa);

    Pessoa* p4 = newPessoa("Inserted", 40);
    l->insert(l,1, p4);

    l->foreach(l, printPessoa);

    void* v = l->pop(l);
    printPessoa(v);
    free(v);

    v = l->pick(l,1);
    printPessoa(v);
    free(v);

    l->foreach(l, printPessoa);

    l->foreach(l, freePessoa); // libera o resto
    l->free(l);
    free(l);
}

int main() {
    printf("Starting tests...\n");
    testInts();
    testStrings();
    testFloats();
    testDoubles();
    testPessoa();
    printf("\nAll tests completed.\n");
    return 0;
}
