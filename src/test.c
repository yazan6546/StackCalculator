//
// Created by yazan on 4/17/2025.
//

#include "dynamic_array.h"
#include "Stack.h"
#include "utils.h"
#include "LinkedList.h"

void removeOperators (Stack *stack, struct node_list *list, char op);
void removePar(struct node_list *s);
void undoReverse (struct node_list* l);
char* convertInfixToPostfix(char *s);
char* convertToPrefix(char *infix);

int main() {

    while (1) {
        char s[100];
        char *out;
        scanf("%s", s);
        char *res = convertToPrefix(s);
        printf("Postfix: %s\n", res);

        printf("\n");
    }

    size_t x = 0;
    printf("%llu", x);
}

char* convertInfixToPostfix(char *s) {
    Stack *st = createStack();
    size_t sz = strlen(s);
    char *res = malloc(2 * sz + 1); // Allocate enough space for the result (considering spaces)
    res[0] = '\0'; // Initialize as an empty string

    for (int i = 0; i < sz; i++) {
        if (isdigit(s[i])) {
            // Handle multi-digit numbers
            while (i < sz && isdigit(s[i])) {
                strncat(res, (char[2]){s[i], '\0'}, 1);
                i++;
            }
            strcat(res, " "); // Add a space after the number
            i--; // Adjust index since the loop increments it
        } else if (isalpha(s[i])) {
            // Handle single-character variables
            strncat(res, (char[3]){s[i], ' ', '\0'}, 2);
        } else if (s[i] == '(') {
            push(st, s[i]);
        } else if (s[i] == ')') {
            // Pop until '(' is found
            while (!isEmpty_stack(st) && st->top != '(') {
                strncat(res, (char[3]){pop(st), ' ', '\0'}, 2);
            }
            if (!isEmpty_stack(st)) {
                pop(st); // Remove '('
            }
        } else {
            // Handle operators
            while (!isEmpty_stack(st) && operatorPrecedence(st->top) <=
                operatorPrecedence(s[i])) {
                strncat(res, (char[3]){pop(st), ' ', '\0'}, 2);
            }
            push(st, s[i]);
        }
    }

    // Pop remaining operators
    while (!isEmpty_stack(st)) {
        strncat(res, (char[3]){pop(st), ' ', '\0'}, 2);
    }

    deleteStack(st); // Free the stack
    return res;
}

// Convert infix expression to prefix notation
char* convertToPrefix(char *infix) {
    reverseString(infix);

    char *postfix = convertInfixToPostfix(infix);

    reverseString(postfix);
    return postfix;
}
