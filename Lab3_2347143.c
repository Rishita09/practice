#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

struct Stack {
    int top;
    unsigned capacity;
    double* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (double*)malloc(stack->capacity * sizeof(double));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, double item) {
    stack->array[++stack->top] = item;
}

double pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return -1;
}

double peek(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top];
    return -1;
}

int precedence(char operator) {
    if (operator == '+' || operator == '-')
        return 1;
    else if (operator == '*' || operator == '/')
        return 2;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    struct Stack* stack = createStack(MAX_SIZE);
    int i, j;
    i = j = 0;

    while (infix[i] != '\0') {
        char current = infix[i];

        if (isdigit(current) || current == '.') {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (current == '(') {
            push(stack, current);
        } else if (current == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
                postfix[j++] = ' ';
            }
            if (!isEmpty(stack) && peek(stack) == '(') {
                pop(stack);
            }
        } else {
            while (!isEmpty(stack) && precedence(current) <= precedence(peek(stack))) {
                postfix[j++] = pop(stack);
                postfix[j++] = ' ';
            }
            push(stack, current);
        }

        i++;
    }

    while (!isEmpty(stack)) {
        postfix[j++] = pop(stack);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

double evaluatePostfix(char* postfix) {
    struct Stack* stack = createStack(MAX_SIZE);
    int i = 0;

    while (postfix[i] != '\0') {
        char current = postfix[i];

        if (isdigit(current) || current == '.') {
            push(stack, atof(&postfix[i]));
            while (isdigit(postfix[i]) || postfix[i] == '.') {
                i++;
            }
            i--;
        } else if (current == ' ') {
            // Skip whitespace
        } else {
            double operand2 = pop(stack);
            double operand1 = pop(stack);

            switch (current) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
            }
        }

        i++;
    }

    return pop(stack);
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Enter a financial expression: ");
    scanf("%[^\n]s", infix);  // Read the whole line, including spaces

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    double result = evaluatePostfix(postfix);
    printf("Result after evaluation: %.2f\n", result);

    return 0;
}

