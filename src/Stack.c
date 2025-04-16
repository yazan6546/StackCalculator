//
// Created by yazan on 4/17/2025.
//

#include "Stack.h"
#include "dynamic_array.h"

Stack* createStack() {

    Stack *s = malloc(sizeof(Stack));

    if (s == NULL) {
        printf("Out of memory!");
        exit(1);
    }

    s->array = createDynamicArray(5);

    if (s->array == NULL) {
        printf("Out of memory!");
        exit(1);
    }

    return s;
}

void deleteStack (Stack* s) {

    free(s->array);
    free(s);
}


int pop(Stack* s) {
    return deleteTopElement(s->array);
}

void push(Stack* s, int data) {
    addElement(s->array, data);
}


int isEmpty_stack(Stack* s) {
    return s->array->size < 1;
}