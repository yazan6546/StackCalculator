//
// Created by yazan on 4/17/2025.
//


#include "LinkedList.h"

struct node_list* makeEmpty_list(struct node_list* L) { //makeEmpty_list

    if (L != NULL) { //L points to some head node_list
        deleteList_list(L);
    }
    L = malloc(sizeof(struct node_list));

    if (L == NULL) {
        printf("out of memory!\n");
        exit(1);
    }

    L -> next = NULL;
    return L;
}

//pass an array and return a linked list

struct node_list* fromArray(char** array, int length) {

    struct node_list* L = NULL;
    L = makeEmpty_list(L);

    for (int i = 0;i<length;i++) {

        addLast_list(L, array[i]);
    }

    return L;
}

void deleteList_list(struct node_list* L) {

    struct node_list* p;
    p = L -> next;
    L -> next = NULL;
    free(L);

    while (p!=NULL) {
        struct node_list* temp = p->next;
        deleteNode(p);
        p = temp;
    }
}

int isEmpty_list(struct node_list* L) {
    return L->next == NULL;
}

int getSize(struct node_list* L) {

    int size = 0;
    for (struct node_list* p = L->next; p != NULL; p = p->next) {
        size++;
    }

    return size;
}




struct node_list* getLastNode_list(struct node_list* L) {

    struct node_list *p = L;

    while (!isLast_list(L, p)) {
        p = p->next;
    }

    return p;
}



void addLast_list(struct node_list* L, char* data) {

    struct node_list* newNode = malloc(sizeof(struct node_list));

    if (newNode == NULL) {
        printf("Out of memory!");
        exit(1);
    }

    struct node_list* p = L;
    while (p -> next != NULL) {
        p = p->next;
    }

    const size_t length = strlen(data);

    char *temp = malloc(length + 1);

    if (temp == NULL) {
        printf("out of memory");
        exit(1);
    }
    strncpy(temp, data, length + 1);
    temp[length] = '\0';

    p->next = newNode;
    newNode -> next = NULL;
    newNode -> data = temp;
}

void addFirst_list (struct node_list* L, char* data) {

    struct node_list * newNode = malloc(sizeof(struct node_list));
    if (newNode == NULL) {
        printf("Out of memory!");
        exit(1);
    }

    const size_t length = strlen(data);

    char *temp = malloc(length + 1);
    strncpy(temp, data, length + 1);
    temp[length] = '\0';

    newNode->next = L->next;
    L->next = newNode;
    newNode -> data = temp;
}

void printList_list(struct node_list* L) {

    if (isEmpty_list(L)) {
        printf("The list is empty!");
        return;
    }

    for (struct node_list* p = L->next; p != NULL; p = p->next) {
        printf("%s ", p->data);
    }
}

int isLast_list(struct node_list* L, struct node_list* p) {

    return (p->next == NULL);
}

//returns the index of the element to which this data belongs
int find(struct node_list* L, char* data) {

}

int findIndex(struct node_list* L, struct node_list* p) {

    int flag = 0;
    int index = 0;

    for (struct node_list* temp = L->next; temp != NULL; temp = temp->next) {
        if (temp == p) {
            flag = 1;
            break;
        }
        index++;
    }

    if (flag) {
        return index;
    }
    return -1;
}

struct node_list* findNode_list (struct node_list* L, int index) {

    if (index < 0 || index >= getSize(L)) {
        return NULL;
    }

    struct node_list *p = L->next;
    for (int i = 0;i<index; i++) {
        p = p->next;
    }

    return p;
}

//finds the node_list before this one, analogous to next.
struct node_list* findPrevious_p (struct node_list* L, struct node_list* p) {

    struct node_list* temp = L;
    int flag = 0;

    while (temp -> next != NULL) {
        if (temp -> next == p) {
            flag = 1;
            break;
        }
        temp = temp -> next;
    }

    return flag? temp : NULL;
}

struct node_list* findPrevious_int (struct node_list* L, char* data) {

    struct node_list* p = L;
    int flag = 0;

    while (p -> next != NULL) {
        if (p -> next -> data == data) {
            flag = 1;
            break;
        }
        p = p->next;
    }

    return flag? p : NULL;
}

//remove the first occurrence of this letter in the list

void remove_int (struct node_list* L, char* data) {

    struct node_list* prev = findPrevious_int(L, data);

    if (prev == NULL) {
        printf("Data not found!\n");
        return;
    }
    struct node_list *temp = prev -> next;
    prev -> next = temp -> next;

    free(temp);
}

void remove_p (struct node_list* L, struct node_list *p) {

    struct node_list* prev = findPrevious_p(L, p);

    if (prev == NULL) {
        printf("Element not found\n");
        return;
    }

    struct node_list* temp = prev -> next;
    prev->next = temp -> next;
    deleteNode(temp);
}

char* removeFirst(struct node_list* L) {

    char* data;
    struct node_list* temp = L->next;
    L -> next = temp -> next;
    data = temp -> data;
    free(temp);

    return data;
}

char* removeLast(struct node_list* L) {

    if (isEmpty_list(L)) {

        printf("List is empty!");
        exit(99);
    }
    struct node_list *p = L;

    while (!isLast_list(L, p->next)) {
        p = p->next;
    }
    struct node_list *temp = p->next;
    char* data = temp -> data;
    p->next = NULL;
    free(temp);

    return data;

}



void reverseList(struct node_list* L) {

    if (isEmpty_list(L)) {
        return;
    }

    struct node_list* p = getLastNode_list(L);
    struct node_list* temp = p;

    while (p->next != L) {
        p->next = findPrevious_p(L, p);
        p = p->next;
    }

    p->next = NULL;
    L->next = temp;

}



void deleteNode (struct node_list* p) {
    free(p->data);
    free(p);
}