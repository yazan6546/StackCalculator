//
// Created by yazan on 4/17/2025.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node_list {
    char *data;
    struct node_list* next;
};



struct node_list* makeEmpty_list(struct node_list* L);
struct node_list* fromArray(char** array, int length);
void deleteList_list(struct node_list* L);
int isEmpty_list(struct node_list* L);
int getSize(struct node_list* L);
void printList_list(struct node_list* L);
void addFirst_list (struct node_list* L, char* data);
void addLast_list(struct node_list* L, char* data);
char* get_list(struct node_list* L, int index);
char* getFirst(struct node_list* L);
char* getLast_list(struct node_list* L);
struct node_list* getLastNode_list(struct node_list* L);
char* removeFirst(struct node_list* L);
char* removeLast(struct node_list* L);
struct node_list* findNode_list (struct node_list* L, int index);
int isLast_list(struct node_list* L, struct node_list* p);
struct node_list* findPrevious_p (struct node_list* L, struct node_list* p);
struct node_list* findPrevious_int (struct node_list* L, char* data);
void remove_int (struct node_list* L, char* data);
void remove_p (struct node_list* L, struct node_list *p);
struct node_list* concat(struct node_list* l1, struct node_list* l2);
void reverseList(struct node_list* L);
void deleteNode (struct node_list* p);


#endif //LINKEDLIST_H
