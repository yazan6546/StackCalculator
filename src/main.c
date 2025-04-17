/*
 * name : yazan abualown
 * id : 1210145
 */

#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "Stack.h"
#include "dynamic_array.h"
#include "LinkedList.h"



int checkValidity(char *string, char *reason);
int isOperator (char c);
char* readString ();
int compare (char i, char j);
int isdigit_string (char *s);
void removeOperators (Stack *stack, struct node_list *list, char op);
void removePar(struct node_list *s);
struct node_list* infix_to_postfix (char *s);
int readFile (char **s, FILE *p);
char** getListFile (FILE *p, int *length);
char reverseParanthesis (char par);
void createSubString (char *string, char *start, char par);
int evaluatePreFix (struct node_list* list);
int isOpening (char p);
int isClosing (char p);
int isBalanced (char *string, char *reason);
char* getParanthesis (char *string);
void reverseString (char *s);
int contains (char q, char *string);
void undoReverse (struct node_list* l);
void handleReason (char *string, const char *character, char *reason);
void showMenu ();
void printStatus (char **arr, int length);
void convertToInfix (struct node_list** arr, int length);
void evaluatePrefix1 (struct node_list **arr, int length);


int main () {

    printf("Enter the name of the input file\n");
    char name[20];


    int length;

    FILE *p = fopen("../inputs.txt", "r");

    if (p == NULL) {
        printf("File not found!\n");
        exit(1);
    }

    char **array = getListFile(p, &length);

     // FILE *q = fopen("output.txt", "w");



    for (int i = 0; i<length;i++) {
        printf("%s\n", array[i]);
    }

    struct node_list** list = malloc(sizeof(struct node_list*) * length+1);
    if (list == NULL) {
        printf("Out of memory!");
        exit(1);
    }

    for (int i = 0;i<length;i++) {
        char n[20];
        // bool valid = checkValidity(list[i]->data, n);
        // printf("okok\n");
        // fflush(stdout);
        // if (valid) {
            list[i] = infix_to_postfix(array[i]);
        // }
    }
    int i;

    while (1) {
        showMenu();
        scanf("%d", &i);

        switch (i) {

            case 1 :
                printStatus(array, length);
                break;

            case 2 :
                convertToInfix(list, length);
                break;

            case 3 :
                evaluatePrefix1(list, length);
                break;

            case 4:
                for (int i = 0; i < length; i++) {
                    char m[20];
                    if (!checkValidity(array[i], m)) {
                        printf("Invalid equation :  %s\n", array[i]);
                    }
                }
                break;

            case 5:
                exit(0);
        }




        }

}



void showMenu () {

    printf("*******Prefix Calculator*******\n\n");
    printf("1- Check the validity of equations.\n");
    printf("2- Convert valid equations from infix to prefix.\n");
    printf("3- Evaluate the prefix\n");
    printf("4- Print invalid equations.\n");
    printf("5- Output to file.\n");
    printf("6- Exit.\n");

    printf("Choose one of the options above:\n");

}



int checkValidity(char *string, char *reason ) {

    int index;

    fflush(stdout);

    char *Par = getParanthesis(string);
    char *q = string;
    int flag = 0;

    if (!isBalanced(Par, reason)) {
        return 0;
    }

    if (!isOperator(*q) && !isdigit(*q) && !contains(*q, "[({<])}>")) {

        sprintf(reason, "Invalid character %c", *q);
        return 0;
    }

    for (;*(q+1) ;q++) { //searching the string

        if (isOperator(*q)) {
            flag = 1;
        }

        if (!isOperator(*(q+1)) && !isdigit(*(q+1)) && !contains(*(q+1), "[({<])}>")) {

            sprintf(reason, "Invalid character %c", *(q+1));
            return 0;
        }


        if (isdigit(*q) && !(isOperator(*(q+1)) || contains(*(q+1), ")]}>") || isdigit(*(q+1)))) {

            handleReason(string, q, reason);
            return 0;
        }
        if (isOperator(*q) && !(isdigit(*(q+1)) || contains(*(q+1), "([{<") || (*(q+1) == '-') )) {
            handleReason(string, q, reason);
            return 0;
        }
        if (isOperator(*q) && (isOperator(*(q+1))) && (*(q+1) != '-')) {
            sprintf(string, "2 operators %c and %c cannot be beside eachother!");
            return 0;
        }
        if (isOpening(*q) && !(isOpening(*(q+1)) || isdigit(*(q+1)) || (*(q+1) == '-'))) {

            printf("errr\n");
            printf("Error with %c and %c as they cannot be beside eachother ", *q, *(q+1));
            strcpy(reason, "");
            return 0;
        }
        else if (isClosing(*q) && !(isClosing(*(q+1)) || isOperator(*(q+1)) || (*(q+1) == '-'))) {
            handleReason(string, q, reason);
            return 0;
        }
    }

    if (isOperator(*q)) {
        sprintf(reason, "No number after operator %c", *q);
        return 0;
    }

    if (!flag) {
        sprintf(reason, "No operator in the whole equation!");
        return 0;
    }

    return 1;
}


char* readString () {

    char *s = malloc(100);
    if (s == NULL) {
        printf("Out of memory!");
        exit(1);
    }
    int i = 0;
    char n;

    while ((n = getchar())!= '\n') {
        if (n != ' ') {
            s[i] = n;
            i++;
        }
    }

    s[i] = '\0';

    char* s_new = realloc(s, i+1);

    if (s_new == NULL) {
        printf("Out of memory!");
        exit(1);
    }
    if (s_new != s) {
        s = s_new;
        s_new = NULL;
    }

    return s;
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



int isdigit_string (char *s) {

    for (char *q = s; *q; q++) {
        if (!isdigit(*q)) {
            return 0;
        }
    }
    return 1;
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


int readFile (char **s, FILE *p) {

    int i = 0;
    char n;

    *s = malloc(30);

    while ((n = getc(p))!= '\n' && (n!=EOF)) {
        if (n != ' ') {
            (*s)[i] = n;
            i++;
        }
    }

    (*s)[i] = '\0';

    // char *new = realloc(*s, i+1);
    //
    // if (new == NULL) {
    //     printf("Failed");
    //     exit(1);
    // }
    // if (new != *s) {
    //     *s = new;
    //     new = NULL;
    // }

    return n;
}

/*
 * read the file and return a list of strings
 * each string is a line in the file
 * length is the number of lines in the file
 */

char** getListFile (FILE *p, int *length) {

    *length = 0;
    char** stringList = calloc(50 , sizeof(char*));
    char *m;
    int n;
    int count = 0;

    while (((n = readFile(&m, p))) && (count < 1)) {

        if (n == -1)  {
            break;
        }
        if (m[0] == 0) {
            break;
        }

        stringList[(*length)++] = m;
    }


    return stringList;
}




int evaluatePreFix (struct node_list* list) {

    int number, number1, number2;

    Stack *stack = NULL;
    stack = createStack(stack);

    reverseList(list);


    for (struct node_list* p = list->next;p!=NULL;p=p->next) {

        if (isdigit(p->data[0])) {
            number = atoi(p->data);
            push(stack, number);
        }
        else if (isOperator(p->data[0])) {
            number1 = pop(stack);
            number2 = pop(stack);

            switch (p->data[0]) {

                case '+' :
                    push(stack, number1 + number2);
                    break;

                case '-' :
                    push(stack, number1 - number2);
                    break;

                case '/' :
                    push(stack, number1 / number2);
                    break;

                case '*' :
                    push(stack, number1 * number2);
                    break;

            }


        }
    }

    reverseList(list);
    int top = stack->top;
    deleteStack(stack);
    return top;
}


int isBalanced (char *string, char *reason) {

    Stack *stack = NULL;
    stack = createStack(stack);

    int index;

    for (char *q = string;*q;q++) {

        if (contains(*q, "[({<")) {

            push(stack, *q);

        }
        else if (contains(*q, "])}>") && isEmpty_stack(stack)) {

            sprintf(reason, "%c does not have an opening", *q);
            return 0;

        }
        else if (((index = contains(*q, "])}>"))) && ((stack->top) == "[({<"[index - 1])) {
            pop(stack);
        }
    }

    if (!isEmpty_stack(stack)) {
        sprintf(reason, "%c is not closed!", stack->top);
        return 0;
    }
    deleteStack(stack);
    return 1;


}


void undoReverse (struct node_list* l) {

    for (struct node_list* p = l->next;p!=NULL;p = p->next) {

        reverseString(p->data);
    }
}

void handleReason (char *string, const char *character, char *reason) {
    //only enters if incorrect.

    if (isdigit(*character) && !isOperator(*(character + 1) )) {

            sprintf(reason, "No operator between %c and %c", *character, *(character+1));
    }
    else if (isOperator(*character) && contains(*character,")]}>")) {
        sprintf(reason, "Error with %c and %c as they cannot be beside eachother", *character, *(character+1));
    }
    else if (isOperator(*character) && isOperator(*(character+1) && (*(character+1) != '-'))) {
        sprintf(reason, "error with operators %c and %c as they cannot be beside each other.", *character, *(character+1));
    }

    else if (isOpening(*character) || isClosing(*character)) {
        sprintf(reason, "Error with %c and %c as they cannot be beside eachother", *character, *(character+1));
    }
    else if (isOperator(*character) && (isOperator(*(character+1))) && (*(character+1) != '-')) {
        sprintf(string, "2 operators %c and %c cannot be beside eachother!");
    }
    else {
        sprintf(string, "2 operators %c and %c cannot be beside eachother!");
    }
}

void printStatus (char **arr, int length) {

    char reason[20];
    for (int i = 0;i<length;i++) {
        if (checkValidity(arr[i], reason)) {
            printf("Equation No. %d -> valid\n", i+1);
        }
        else {
            printf("Equation No. %d invalid : %s\n", i+1, reason);
            }
        }
}

void convertToInfix (struct node_list** arr, int length) {

    struct node_list* list;

    char s[20];
    for (int i = 0;i<length;i++) {
        printList_list(arr);
    }
}

void evaluatePrefix1 (struct node_list **arr, int length) {

    for (int i = 0;i<length;i++) {
        int v = evaluatePreFix(arr[i]);
        printf("Equation No %d : %d", i+1, v);
    }

}