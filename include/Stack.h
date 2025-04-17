//
// Created by yazan on 4/17/2025.
//

#ifndef STACK_H
#define STACK_H

#include "dynamic_array.h"

typedef struct {
    char top;
    dynamic_array* array;

} Stack;

Stack* createStack();
void deleteStack (Stack* s);
char pop(Stack* s);
void push(Stack* s, int data);
int isEmpty_stack(Stack* s);

#endif //STACK_H
