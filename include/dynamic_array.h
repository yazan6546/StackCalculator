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
    int *array;
    int size;
    int capacity;
} dynamic_array;

dynamic_array* createDynamicArray(int capacity);
void deleteDynamicArray(dynamic_array* arr);
void addElement(dynamic_array* arr, int element);
int deleteTopElement(dynamic_array* arr);
int getElement(const dynamic_array* arr, int index);
void printDynamicArray(const dynamic_array* arr);
void resizeDynamicArray(dynamic_array* arr, int new_capacity);



#endif //DYNAMIC_ARRAY_H
