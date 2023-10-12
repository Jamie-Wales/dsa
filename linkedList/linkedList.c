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

void push(Queue *self, void *item, size_t size) {
    Node *node;
    node = calloc(1, sizeof(Node));
    if (node == NULL) {
        printf("Memory Allocation Failed!/n");
        exit(1);
    }

    node->value = calloc(1, sizeof(size_t));
    memcpy(node->value, item, size);
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

void front(Queue *self, void *value, size_t size) {

    Node *head = self->linkedList->head;
    Node *newHead = calloc(1, sizeof(Node));
    newHead->value = calloc(1, sizeof(size));
    memcpy(newHead->value, value, size);
    self->linkedList->head = newHead;

    if (head == NULL) {
        self->linkedList->head = newHead;
        self->linkedList-> tail = newHead;
    }

    newHead->next = head;
    self->linkedList->size++;

}

void *pop(Queue *self) {
    if (self->linkedList->size == 0) {
        return NULL;
    }

    LinkedList *list = self->linkedList;
    Node *oldHead = list->head;
    list->size--;
    list->head = list->head->next;


    void *value = oldHead->value;
    free(oldHead);
    if (list->size == 0) {
        list->head = NULL;
        list->tail = NULL;
    }
    return value;
}

void *deTail(Queue *self) {
    if (self->linkedList->size == 0) {
        return NULL;
    }

    if (self->linkedList->size == 1) {
        void *element = self->linkedList->head->value;
        self->linkedList->head = NULL;
        self->linkedList->tail = NULL;
        self->linkedList->size--;
        free(self->linkedList->head);
        return element;

    }

    LinkedList *list = self->linkedList;
    Node *prev;
    Node *head = list->head;

    while (head->next != NULL) {
        prev = head;
        head = head->next;
    }


    list->tail = prev;
    list->tail->next = NULL;
    list->size--;
    void *value = head->value;
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
    }
}

void *current(Iterator *self) {
    if (self->linkedList->head != NULL)  {
       return self->linkedList->head->value;
    } else {
        return NULL;
    }
}

void destroyIterator(Iterator *self) {
    free(self);
}


IteratorInterface iteratorInterface = {
        .hasNext = hasNext,
        .next = next,
        .current = current,
        .destroyIterator = destroyIterator,
};


Iterator *createIterator(Queue *self, size_t size) {
    Iterator *itr = calloc(1, sizeof(Iterator));

    // Deep copy linked list
    itr->linkedList = calloc(1, sizeof(LinkedList));
    Node *current = self->linkedList->head;
    Node *itrCurrent = NULL;

    while (current != NULL) {
        Node *newNode = calloc(1, sizeof(Node));

        newNode->value = malloc(sizeof(size));
        memcpy(newNode->value, self->linkedList->head->value, size);
        newNode->next = NULL;
        if (itrCurrent == NULL) {
            itr->linkedList->head = newNode;
            itrCurrent = newNode;
        } else {
            itrCurrent->next = newNode;
            itrCurrent = itrCurrent->next;
        }

        itrCurrent->next = NULL;
        current = current->next;
    }

    itr->linkedList->tail = itrCurrent;
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
        .front = front,
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

    head->value = calloc(1, sizeof(Node));
    memcpy(head->value, value, size);
    list->head = head;
    list->tail = head;
    list->size = 1;
    head->next = NULL;



    Queue queue = {
            .queueInterface = &interface,
            .linkedList = list,
    };

    return queue;

}

