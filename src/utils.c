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

int compare (const char i, const char j) {

    if (!isOperator(j)) {
        return 2;
    }

    if ((i == j) || (i + 5 == j)) {
        return 0;
    }
    if ((i == '+') && (j == '-') || ((j == '+') && (i == '-'))) {
        return 0;
    }
    if ((i == '*') || (i == '/') || i == '^') {
        return 1;
    }

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
