//
// Created by yazan on 4/17/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* getParanthesis (char *string);
void reverseString (char *s);
int contains (char q, char *string);
int compare (const char i, const char j);
int isOperator (char c);
int isOpening (char p);
int isClosing (char p);
#endif //UTILS_H
