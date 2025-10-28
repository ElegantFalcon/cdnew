#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char stack[50];
int top = -1;

int tempCount = 1;

void push(char c)
{
    stack[++top] = c;
}

char pop()
{
    return stack[top--];
}

char peek()
{
    return stack[top];
}

int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

void intopost(char infix[], char postfix[])
{
    int i, k = 0;
    char c;

    for (i = 0; (c = infix[i]) != '\0'; i++)
    {
        if (isalnum(c))
        {
            postfix[k++] = c;
        }

        else if (c == '(')
        {
            push(c);
        }

        else if (c == ')')
        {
            while (top != -1 && peek() != '(')
            {
                postfix[k++] = pop();
            }
            pop();
        }

        else
        {
            while (top != -1 && precedence(peek()) >= precedence(c))
            {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    while (top != -1)
    {
        postfix[k++] = pop();
    }

    postfix[k] = '\0';
}

void generateTAC(char postfix[], char lhs)
{
    char stack2[50][10];
    int top2 = -1;
    char op1[10], op2[10], temp[10];
    char c;

    for (int i = 0; (c = postfix[i]) != '\0'; i++)
    {
        if (isalnum(c))
        {
            char s[2] = {c, '\0'};
            strcpy(stack2[++top2], s);
        }
        else
        {
            strcpy(op2, stack2[top2--]);
            strcpy(op1, stack2[top2--]);
            sprintf(temp, "t%d", tempCount++);
            printf("%s = %s %c %s \n", temp, op1, c, op2);
            strcpy(stack2[++top2], temp);
        }
    }

    printf("%c = %s\n", lhs, stack2[top2]);
}

int main()
{
    char infix[50], postfix[50];
    char lhs;

    printf("enter expresiion : ");
    scanf("%s", infix);

    lhs = infix[0];
    char rhs[50];
    strcpy(rhs, &infix[2]);

    intopost(rhs, postfix);

    printf("\n Postfix : %s \n", postfix);
    printf("\n TAC : \n");
    generateTAC(postfix, lhs);

    return 0;
}