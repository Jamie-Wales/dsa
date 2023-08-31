//
// Created by jamie on 8/30/23.
//

#ifndef MYFIRSTC_LINKEDLIST_H
#define MYFIRSTC_LINKEDLIST_H

#include <malloc.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    void * value;
    Node * next;
};

typedef struct LinkedList {
    Node * head;
    Node * tail;
    int size;
} LinkedList;

typedef struct Queue Queue;

typedef struct Iterator Iterator;


typedef struct {
    void (*init)(Queue *queue, Iterator *self);
    _Bool (*hasNext)(Node *head);
    void *(*current)(Node *head);
    void (*next)(Node *head);
} IteratorInterface;



struct Iterator {
    Node *node;
    IteratorInterface *interface;
};




typedef struct {
    void (*create)(Queue *self, void * value);
    void (*destroy)(Queue *self);
    void (*push)(Queue *self, void *item);
    void *(*pop)(Queue *self);
    void (*print)(Queue *self, void *(outputStream)(void *object));
    int (*size)(Queue *self);
} QueueInterface;

struct Queue {
    QueueInterface *interface;
    LinkedList *list;
};

#endif
