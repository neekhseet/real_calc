#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef enum tag_operator
{
    add = '+',
    sub = '-',
    mul = '*',
    divide = '/'
} OPERATOR;

typedef struct tag_operation
{
    int first_number;
    int second_number;
    int result;
    OPERATOR op;
} OPERATION;

void calc(OPERATION *op);
int safe_print(const char *prompt);
void print_operators();

int main(void)
{
    OPERATION op;

    op.first_number = safe_print("Please, enter first number:");
    op.second_number = safe_print("Please, enter second number:");
    print_operators();
    int choice = get_operator_choice();
    
    switch (choice)
    {
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

int get_operator_choice(void)
{
    char buffer[100];
    int choice;
    
    while (1)
    {
        printf("Enter your choice (1-4): ");
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            continue;
        }
        
        if (sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        if (choice >= 1 && choice <= 4)
        {
            return choice;
        }
        
        printf("Invalid choice. Please enter 1, 2, 3, or 4.\n");
    }
}

void print_operators() {
    printf("\n=== Operator Menu ===\n");
    printf("1. Addition (%c)\n", add);
    printf("2. Subtraction (%c)\n", sub);
    printf("3. Multiplication (%c)\n", mul);
    printf("4. Division (%c)\n", divide);
    printf("====================\n");
}


int safe_print(const char *prompt)
{
    char buffer[100];
    char *endptr;
    long i;

    while (1)
    {
        printf("%s\n", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            continue;
        }

        errno = 0;
        i = strtol(buffer, &endptr, 10);

        if (errno == ERANGE || i < INT_MIN || i > INT_MAX)
        {
            printf("Invalid input\n");
            continue;
        }

        if (endptr == buffer)
        {
            printf("Invalid input\n");
            continue;
        }

        return (int)i;
    }
}

void calc(OPERATION *op)
{
    switch (op->op)
    {
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
        if (op->first_number == 0 || op->second_number == 0)
        {
            op->result = 0;
            puts("You can't divide for 0.");

            exit(1);
        }
        op->result = op->first_number / op->second_number;
        break;
    }
}