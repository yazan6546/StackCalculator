//
// Created by yazan on 4/17/2025.
//

#include "dynamic_array.h"
#include "Stack.h"

int main() {
    dynamic_array arr;
    arr.capacity = 5;
    arr.size = 0;
    arr.array = (int*)malloc(arr.capacity * sizeof(int));
    if (arr.array == NULL) {
        printf("Out of memory!");
        exit(1);
    }
    addElement(&arr, 1);
    addElement(&arr, 2);
    addElement(&arr, 3);
    addElement(&arr, 4);
    addElement(&arr, 5);
    addElement(&arr, 6);
    addElement(&arr, 7);
    addElement(&arr, 8);
    addElement(&arr, 9);
    addElement(&arr, 10);
    addElement(&arr, 11);
    addElement(&arr, 12);
    addElement(&arr, 13);
    addElement(&arr, 14);
    addElement(&arr, 15);
    addElement(&arr, 16);
    addElement(&arr, 17);
    addElement(&arr, 18);
    addElement(&arr, 19);
    addElement(&arr, 20);
    for (int i = 0; i < 17; i++) {
        deleteTopElement(&arr);
    }

    printf("%d\n", deleteTopElement(&arr));

    printDynamicArray(&arr);
}
