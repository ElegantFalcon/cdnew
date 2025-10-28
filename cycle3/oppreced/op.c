#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char stack[50], ip[50], opt[10][10][2], ter[10];
    int i, j, k, n, top = 0, col = -1, row = -1;

    for (i = 0; i < 50; i++)
    {
        stack[i] = '\0';
        ip[i] = '\0';
    }

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            opt[i][j][0] = '\0';
        }
    }

    printf("Enter the no of terminals : ");
    scanf("%d", &n);

    printf("\nEnter the terminals as string : ");
    scanf("%s", ter);

    printf("\n Enter the table values : \n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Enter the value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    printf("\n *** Operator precedence table *** \n \t");
    for (i = 0; i < n; i++)
    {
        printf("%c\t", ter[i]);
    }

    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("%c\t", ter[i]);
        for (j = 0; j < n; j++)
        {
            printf("%c\t",opt[i][j][0]);
        }
        printf("\n");
    }


    stack[top] = '$';
    printf("\n Enter input string with $ at the end : ");
    scanf("%s",ip);

    i=0;

    printf("\nSTACK\t\t INPUT STRING \t\t ACTION \n");
    printf("%s\t\t%s\t\t",stack,ip);

    while(i<=strlen(ip)){
        col = row = -1;

        for(k=0;k<n;k++){
            if(stack[top] == ter[k])
                col =k;
            if(ip[i] == ter[k])
                row =k;
        }

        if(col == -1 || row ==-1){
            printf("\n error invalid symbol \n");
            break;
        }

        if((stack[top] == '$') && (ip[i] == '$')){
            printf("String is accepted \n");
            break;
        }

        else if((opt[col][row][0] == '<') || (opt[col][row][0]== '=')){
            stack[++top] = opt[col][row][0];
            stack[++top] = ip[i];
            printf("Shift %c",ip[i]);
            i++;
        }

        else if(opt[col][row][0] == '>'){
            while(stack[top] != '<' && top>0){
                --top;
            }
            top = top-1;
            printf("Reduce");
        }
        else{
            printf("String not accepted");
            break;
        }

        printf("\n");
        for(k=0;k<=top;k++){
            printf("%c",stack[k]);
        }

        printf("\t\t");
        for(k=i;k<strlen(ip);k++){
            printf("%c",ip[k]);
        }
        printf("\t\t");
    }

    return 0;
}