//
// Created by yazan on 4/17/2025.
//

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct dynamic_array {
    char *array;
    size_t size;
    size_t capacity;
} dynamic_array;

dynamic_array* createDynamicArray(size_t capacity);
void deleteDynamicArray(dynamic_array* arr);
void addElement(dynamic_array* arr, char element);
char deleteTopElement(dynamic_array* arr);
char getElement(const dynamic_array* arr, size_t index);
void printDynamicArray(const dynamic_array* arr);
void resizeDynamicArray(dynamic_array* arr, size_t new_capacity);



#endif //DYNAMIC_ARRAY_H
