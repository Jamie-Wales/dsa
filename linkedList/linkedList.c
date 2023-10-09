#include "linkedList.h"

typedef struct Node Node;

struct Node {
    void *value;
    Node *next;
};

typedef struct LinkedList {
    Node *head;
    Node *tail;
    size_t size;
} LinkedList;


void destroy(Queue *self) {
    Node *head = self->linkedList->head;
    while (head != NULL) {
        Node *prev = head;
        head = head->next;
        free(prev->value);
        free(prev);
        prev = NULL;
    }

    free(self->linkedList);
    self->linkedList = NULL;
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

    LinkedList *list = self->linkedList;

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
    if (self->linkedList->size == 0) {
        return NULL;
    }

    LinkedList *list = self->linkedList;
    Node *oldHead = list->head;
    list->head = list->head->next;
    list->size--;
    void *value = oldHead->value;
    free(oldHead);

    return value;
}

void *deTail(Queue *self) {
    if (self->linkedList->size == 0) {
        return NULL;
    }

    LinkedList *list = self->linkedList;
    Node *prev;
    Node *head;

    while(list->head->next != NULL) {
        prev = list->head;
        head = list->head->next;
    }


    prev->next = NULL;
    self->linkedList->tail = prev;
    list->size--;
    void *value = head->next->value;
    free(head);
    return value;
}



void print(Queue *self, void *(outputStream)(void *object)) {
    LinkedList *list = self->linkedList;
    Node *head = list->head;
    while (head != NULL) {
        outputStream(head->value);
        head = head->next;
    }
}

int size(Queue *self) {
    return self->linkedList->size;
}

_Bool hasNext(Iterator *iterator) {
    return iterator->linkedList->head->next != NULL;
}

void next(Iterator *self) {
    if (hasNext(self)) {
        self->linkedList->head = self->linkedList->head->next;
        self->linkedList->head->value;
    }
}

void *current(Iterator *self) {
    return self->linkedList->head->value;
}




IteratorInterface iteratorInterface = {
        .hasNext = hasNext,
        .next = next,
        .current = current,
};

Iterator *createIterator(Queue *self) {
    Iterator *itr = calloc(1, sizeof(Iterator));
    *(itr->linkedList) = *(self->linkedList);
    itr->interface = &iteratorInterface;
    return itr;
}

QueueInterface interface = {
        .destroy = destroy,
        .push = push,
        .pop = pop,
        .print = print,
        .size = size,
        .createIterator = createIterator,
        .deTail = deTail,
};




Queue createQueue(void *value, size_t size) {


    Node *head;
    head = malloc(sizeof(Node));
    LinkedList *list;
    list = malloc(sizeof(LinkedList));

    if (head == NULL || list == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(1);
    }

    head->value = calloc(1, sizeof(size));
    memcpy(head->value, value, size);
    list->head = head;
    list->tail = head;
    list->size = 1;


    Queue queue = {
            .queueInterface = &interface,
            .linkedList = list,
    };

    return queue;

}

