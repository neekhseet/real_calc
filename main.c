#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef enum tag_operator {
    add = '+',
    sub = '-',
    mul = '*',
    divide = '/'
} OPERATOR;

typedef struct tag_operation {
    int first_number;
    int second_number;
    int result;
    OPERATOR op;
} OPERATION;

void calc(OPERATION *op) {
    switch (op->op) {
        case add:
            op->result = op->first_number + op->second_number;
            break;
        case sub:
            op->result = op->first_number - op->second_number;
            break;
        case mul:
            op->result = op->first_number * op->second_number;
            break;
        case divide:
            if (op->first_number == 0 || op->second_number == 0) {
                op->result = 0;
                puts("You can't divide for 0.");

                return;
            }
            op->result = op->first_number / op->second_number;
            break;
    }
}

int main(void) {
    OPERATION op;
    printf("Enter the first number: ");
    char buffer[100];
    char *endptr;
    long i;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    errno = 0;
    i = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || i < INT_MIN || i > INT_MAX ) {
        printf("Invalid input\n");
        return 1;
    }
    if (endptr == buffer) {
        printf("Invalid input\n");
        return 1;
    }
    op.first_number = (int)i;

    printf("Enter the second number: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    errno = 0;
    i = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || i < INT_MIN || i > INT_MAX ) {
        printf("Invalid input\n");
        return 1;
    }
    if (endptr == buffer) {
        printf("Invalid input\n");
        return 1;
    }
    op.second_number = (int)i;

    printf("Choose the operator:\n1. %c\n2. %c\n3. %c\n4. %c\n", add, sub, mul, divide);

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            op.op = add;
            break;
        case 2:
            op.op = sub;
            break;
        case 3:
            op.op = mul;
            break;
        case 4:
            op.op = divide;
            break;
        default:
            puts("Wrong operator!");
            return 1;
    }

    calc(&op);
    printf("The result is: %d\n", op.result);

    return 0;
}