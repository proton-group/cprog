//
// Created by anatoly on 10/28/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct List {
    struct List* parent;
    struct List* child;
    char* data;
} List;

void init(List* a) {
    a -> child = NULL;
    a -> parent = NULL;
    a -> data = NULL;
}

List* list() {
    List* out = malloc(sizeof(List));
    out -> parent = NULL;
    init(out);
    return out;
}

void add(List* a, void* data, size_t dsize, size_t position) {
    if (a == NULL) {
        List *root = malloc(sizeof(List));
        init(root);
        a = root;
    }

    struct List *cur = a;
    int count = 0;
    while(count < position) {
        if (cur->child != NULL) {
            cur = cur->child;
        } else {
            List *new = malloc(sizeof(List));
            new->parent = cur;
            new->child = NULL;
            new->data = NULL;
            cur->child = new;
            cur = new;
        }
    }
        cur->data = (char*) malloc(dsize);
        if (cur -> data == NULL) return;
        memcpy(cur->data, data, dsize);
}

char* read(List* a, size_t position) {
    List *cur = a;
    for (int i = 0; i < position; i++) {
        if (cur->child == NULL) return "Error";
        cur = cur -> child;
    }
    if (cur -> data != NULL) return cur -> data;
    else return "Error";
}

void clear(List* a) {
    List* cur = a;
    List* buf;
    while(cur != NULL) {
        //сначала нужно освободить подструктуры!
        buf = cur;
        cur = cur -> child;
        free(buf -> data);
        free(buf);
    }
}

void delete(List* a, size_t position) {
    List* cur = a;
    for (int i = 0; i < position; i++) {
        cur = cur->child;
    }
    cur -> parent -> child = cur -> child;
    if (cur -> child != NULL) {
        cur -> child -> parent = cur -> parent;
    }
    free(cur);
}

void append(List* a, size_t dsize, void* data) {
    if (a == NULL) {
        List *root = malloc(sizeof(List));
        init(root);
        a = root;
    }

    struct List *cur = a;
    while (cur -> child != NULL) {
        cur = cur->child;
    }
    List* new = malloc(sizeof(List));
    init(new);
    new -> parent = cur;
    cur -> child = new;
    new->data = malloc(dsize);
    memcpy(new->data, data, dsize);
    return;
}

List* prepand(List* a, size_t dsize, void*data) {
    if (a == NULL) {
        List *root = malloc(sizeof(List));
        init(root);
        a = root;
    }

    List* new = malloc(sizeof(List));
    init(new);
    a->parent = new;
    new -> child = a;
    new->data = malloc(dsize);
    memcpy(new->data, data, dsize);
    return new;
}


int main() {
    List* a = list();
    int data = 5;
    append(a, sizeof(int), &data);
    //add(&a, &data, sizeof(int), 3);
    printf("%d\n", read(a, 1)[0]);
    List* b = prepand(a, sizeof(int), &data);
    printf("%d\n", read(b, 0)[0]);
    printf("%d\n", read(b, 2)[0]);
    delete(b, 2);
    printf("%d\n", read(b, 2)[0]);
    clear(a);
    return 0;
}