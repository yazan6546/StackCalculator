//
// Created by yazan on 4/17/2025.
//

#include "dynamic_array.h"
#include "Stack.h"
#include "utils.h"
#include "LinkedList.h"

struct node_list* infix_to_postfix (char *s);
void removeOperators (Stack *stack, struct node_list *list, char op);
void removePar(struct node_list *s);
void undoReverse (struct node_list* l);

int main() {

    while (1) {
        char s[100];
        char *out;
        scanf("%s", s);
        struct node_list *list = infix_to_postfix(s);
        printList_list(list);
        printf("\n");
    }

    size_t x = 0;
    printf("%llu", x);
}

struct node_list* infix_to_postfix (char *s) {

    reverseString(s);
    int index;

    struct node_list *list = NULL;
    list = makeEmpty_list(list);

    Stack *stack = NULL;
    stack = createStack(stack);


    for (char *q = s; *q; q++) {

        const struct node_list *last = getLastNode_list(list);

        if (isEmpty_list(list) && isdigit(*q)) {

            addLast_list(list, (char[10]) {*q, '\0'}); //you cant add any more characters!
        }
        else if (isdigit(*q) && isdigit(*(q - 1))) {

            strcat(last->data, (char[2]) {*q, '\0'});
        }
        else if (isdigit(*q) && !isdigit(*(q - 1))) {

            addLast_list(list, (char[10]) {*q, '\0'});

        }
        else if ((isEmpty_stack(stack) && isOperator(*q)) || (isOperator(*q) && (compare(*q, stack->top) >= 0))) {
            push(stack, *q);
        }
        else if (!isEmpty_stack(stack) && isOperator(*q) && (compare(*q, stack->top) == -1)) {

            removeOperators(stack, list, *q);
            push(stack, *q);
        }

        else if (isOpening(*q)) {
            push(stack, *q);
        }
        else if ((index = contains(*q, ")]}>"))) {

            char reverse = "([{<"[index-1];
            while (stack->top != reverse) {

                char n = pop(stack);

                if (isOperator(n) || isdigit(n)) {

                    addLast_list(list, (char[]) {n, '\0'});
                }
            }
        }

    }
    while (!isEmpty_stack(stack)) {

        char c = pop(stack);
        addLast_list(list, (char[10]) {c, '\0'});

    }
    removePar(list);
    reverseList(list);
    undoReverse(list);
    return list;
}

/*
 * pop operators that have greater precedence than the supplied operator
 * and add to list
 */

void removeOperators (Stack *stack, struct node_list *list, char op) {

    int comp;

    do {
        char c = pop(stack);
        addLast_list(list, (char[]) {c, '\0'});

        comp = compare(op, stack->top);
    } while (comp == -1);
}

void removePar(struct node_list *s) {


    struct node_list *q;
    for (struct node_list *p = s; p!=NULL;) {

        if (contains(p->data[0], "([{)]}")) {
            q = p->next;
            remove_p(s, p);
            p = q;
        }
        else {
            p = p->next;
        }
    }
}

void undoReverse (struct node_list* l) {

    for (struct node_list* p = l->next;p!=NULL;p = p->next) {

        reverseString(p->data);
    }
}
