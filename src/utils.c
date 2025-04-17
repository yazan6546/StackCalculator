//
// Created by yazan on 4/17/2025.
//

#include "utils.h"



char* getParanthesis (char *string) {

    int i = 0;

    char *par = malloc(50);
    for (char *q = string;*q;q++) {

        if (contains(*q ,"([{<)}]>")) {
            par[i++] = *q;
        }
    }

    par[i] = '\0';
    char *new = realloc(par, i+1);

    if (new == NULL) {
        printf("mission failed.");
        exit(1);
    }
    else if (new != par) {
        par = new;
    }

    return par;
}

void reverseString (char *s) {

    const size_t length = strlen(s);

    size_t i, j;
    int index;
    for (i = 0, j = length - 1; i<length/2; i++, j--) {

        if ((index = contains(s[i], "])}>"))) {
            s[i] = "[({<"[index-1];

        }
        else if ((index = contains(s[i], "[({<"))) {
            s[i] = "])}>"[index-1];

        }
        if ((index = contains(s[j], "])}>"))) {
            s[j] = "[({<"[index-1];

        }
        else if ((index = contains(s[j], "[({<"))) {
            s[j] = "])}>"[index-1];

        }

        if (length % 2 != 0 && ((index = contains(s[length / 2], "])}>")))) {
            s[length/2] = "[({<"[index-1];
        }
        else if (length % 2 != 0 && ((index = contains(s[length / 2], "[({<")))) {
            s[length/2] = "])}>"[index-1];
        }

        const char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

int contains (char q, char *string) {
    for (char *m = string ;*m;m++) {
        if (*m == q) {
            return m-string + 1;
        }
    }
    return 0;
}

// Get precedence of operators
int operatorPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return -1;
}


int isOperator (char c) {
    return c >= 42 && c <= 47;
}


int isOpening (char p) {
    return contains(p, "([{<");
}

int isClosing (char p) {
    return contains(p, ")]}>");
}


char** splitString(const char* input, int* count) {
    // Copy the input string to avoid modifying the original
    char* str = strdup(input);
    if (str == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    // Count the number of tokens
    *count = 0;
    char* temp = strdup(input);
    char* token = strtok(temp, " ");
    while (token != NULL) {
        (*count)++;
        token = strtok(NULL, " ");
    }
    free(temp);

    // Allocate memory for the array of strings
    char** result = malloc((*count) * sizeof(char*));
    if (result == NULL) {
        printf("Out of memory!\n");
        free(str);
        exit(1);
    }

    // Tokenize the string and store each token in the array
    int index = 0;
    token = strtok(str, " ");
    while (token != NULL) {
        result[index] = strdup(token);
        if (result[index] == NULL) {
            printf("Out of memory!\n");
            free(str);
            for (int i = 0; i < index; i++) {
                free(result[i]);
            }
            free(result);
            exit(1);
        }
        index++;
        token = strtok(NULL, " ");
    }

    free(str);
    return result;
}
