//
// Created by yazan on 4/17/2025.
//

#ifndef STACK_H
#define STACK_H

#include "dynamic_array.h"

typedef struct {
    int top;
    dynamic_array* array;

} Stack;

Stack* createStack();
void deleteStack (Stack* s);
int pop(Stack* s);
void push(Stack* s, int data);
void doubleCapacity(Stack* s);
int isEmpty_stack(Stack* s);

#endif //STACK_H
