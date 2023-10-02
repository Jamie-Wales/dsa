#include <string.h>
#include "linkedList.h"

void create(Queue *self, void *value, unsigned long size) {
    Node *head;
    head = malloc(sizeof(Node));
    LinkedList *list;
    list = malloc(sizeof(LinkedList));
    void *item = malloc(sizeof(size));
    memcpy(item, value, size);


    if (head == NULL || list == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(1);
    }

    head->value = item;
    self->list = list;
    self->list->head = head;
    self->list->tail = head;
    self->list->size = 1;
}

void destroy(Queue *self) {
    Node *head = self->list->head;
    while (head != NULL) {
        Node *prev = head;
        head = head->next;
        free(prev->value);
        free(prev);
        prev = NULL;
    }

    free(self->list);
    self->list = NULL;
}

void push(Queue *self, void *item) {
    Node *node;
    node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory Allocation Failed!/n");
        exit(1);
    }

    node->value = item;
    node->next = NULL; // Important to initialize to NULL

    LinkedList *list = self->list;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

void *pop(Queue *self) {
    if (self->list->size == 0) {
        return self;
    }

    LinkedList *list = self->list;
    Node *oldHead = list->head;
    list->head = list->head->next;
    list->size--;
    void *value = oldHead->value;
    free(oldHead);

    return value;
}

void print(Queue *self, void *(outputStream)(void *object)) {
    LinkedList *list = self->list;
    Node *head = list->head;
    while (head != NULL) {
        outputStream(head->value);
        head = head->next;
    }
}

int size(Queue *self) {
    return self->list->size;
}

QueueInterface interface = {
    .create = create,
    .destroy = destroy,
    .push = push,
    .pop = pop,
    .print = print,
    .size = size,
};

void init(Queue *queue, Iterator *iterator) {
    iterator->node = queue->list->head;
}

_Bool hasNext(Node *head) {
    return head->next != NULL;
}

void *current(Node *head) {
    return head->value;
}

void next(Node *head) {
    if (head->next != NULL) {
        Node *prev = head;
        head = head->next;
        free(prev);
        prev = NULL;
    }
}

void destroyIterator(Iterator * self) {
    self->node = NULL;
}

IteratorInterface iteratorInterface = {
    .init = init,
    .hasNext = hasNext,
    .current = current,
    .next = next,
    .destroyIterator = destroyIterator
};