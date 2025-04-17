/*
 * name : yazan abualown
 * id : 1210145
 */

#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <utils.h>

#include "Stack.h"
#include "dynamic_array.h"
#include "LinkedList.h"



int checkValidity(char *string, char *reason);
char* readString ();
int compare (char i, char j);
int isdigit_string (char *s);
void removeOperators (Stack *stack, struct node_list *list, char op);
void removePar(struct node_list *s);
int readFile (char **s, FILE *p);
char** getListFile (FILE *p, int *length);
char reverseParanthesis (char par);
void createSubString (char *string, char *start, char par);
int evaluatePreFix (struct node_list* list);
int isBalanced (char *string, char *reason);
void undoReverse (struct node_list* l);
void handleReason (char *string, const char *character, char *reason);
void showMenu ();
void printStatus (char **arr, int length);
void convertToInfix (struct node_list** arr, int length);
void evaluatePrefix1 (struct node_list **arr, int length);

char* convertInfixToPostfix(char *s);
char* convertToPrefix(char *infix);

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
        array[i] = convertToPrefix(array[i]);
        printf("%s\n", array[i]);
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
        if (isClosing(*q) && !(isClosing(*(q+1)) || isOperator(*(q+1)) || (*(q+1) == '-'))) {
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
            push(st, s[i]); // Push '(' to the stack
        } else if (s[i] == ')') {
            // Pop until '(' is found, but do not append '(' or ')' to the result
            while (!isEmpty_stack(st) && st->top != '(') {
                strncat(res, (char[3]){pop(st), ' ', '\0'}, 2);
            }
            if (!isEmpty_stack(st)) {
                pop(st); // Remove '('
            }
        } else {
            // Handle operators
            while (!isEmpty_stack(st) && operatorPrecedence(st->top) <= operatorPrecedence(s[i])) {
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
    free(infix); // Free the reversed infix string
    return postfix;
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