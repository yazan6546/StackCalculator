//
// Created by yazan on 4/17/2025.
//

#include "dynamic_array.h"

dynamic_array* createDynamicArray(const int capacity) {
    dynamic_array* arr = (dynamic_array*)malloc(sizeof(dynamic_array));
    arr->capacity = capacity;
    arr->size = 0;
    arr->array = (int*)malloc(capacity * sizeof(int));
    return arr;
}

void deleteDynamicArray(dynamic_array* arr) {
    free(arr->array);
    free(arr);
}

void resizeDynamicArray(dynamic_array* arr, const int new_capacity) {
    arr->capacity = new_capacity;
    int *temp = (int*)realloc(arr->array, arr->capacity * sizeof(int));

    if (temp == NULL) {
        printf("Reallocation failed!");
        exit(1);
    }

    arr->array = temp;
}


void addElement(dynamic_array* arr, const int element) {
    if (arr->size >= arr->capacity) {
        resizeDynamicArray(arr, arr->capacity * 2);
    }
    arr->array[arr->size++] = element;
}

int getElement(const dynamic_array* arr, const int index) {
    if (index < 0 || index >= arr->size) {
        printf("Index out of bounds!");
        exit(1);
    }
    return arr->array[index];
}

int deleteTopElement(dynamic_array* arr) {
    if (arr->size == 0) {
        printf("Array is empty!");
        exit(1);
    }
    arr->size--;
    int temp =  arr->array[arr->size];

    if (arr->size < arr->capacity / 4) {
        resizeDynamicArray(arr, arr->capacity / 2);
    }
    return temp;
}

void printDynamicArray(const dynamic_array* arr) {
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->array[i]);
    }
    printf("\n");
}
