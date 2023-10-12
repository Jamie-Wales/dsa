#ifndef MYFIRSTC_LINKEDLIST_H
#define MYFIRSTC_LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct LinkedList LinkedList;
typedef struct QueueInterface QueueInterface;

typedef struct Queue {
    QueueInterface *queueInterface;
    LinkedList *linkedList;
} Queue;

typedef struct IteratorInterface IteratorInterface;

typedef struct Iterator {
    LinkedList *linkedList;
    IteratorInterface *interface;
} Iterator;

struct IteratorInterface {
    _Bool (*hasNext)(Iterator *iterator);

    void (*next)(Iterator *iterator);

    void *(*current)(Iterator *iterator);

    void (*destroyIterator)(Iterator *iterator);
};

struct QueueInterface {
    void (*front)(Queue *self, void *item, size_t size);

    void (*destroy)(Queue *self);

    void (*push)(Queue *self, void *item, size_t size);

    void *(*pop)(Queue *self);

    void (*print)(Queue *self, void *(outputStream)(void *object));

    int (*size)(Queue *self);

    Iterator *(*createIterator)(Queue *self, size_t size);

    void *(*deTail)(Queue *self);
};

Queue createQueue(void *value, size_t size);

#endif
