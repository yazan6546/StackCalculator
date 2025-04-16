//
// Created by yazan on 4/17/2025.
//

#include "dynamic_array.h"
#include "Stack.h"
#include "utils.h"

int main() {

    while (1) {
        char s[100];
        char *out;
        scanf("%s", s);
        out = getParanthesis(s);
        printf("%s\n\n", out);
    }
}
