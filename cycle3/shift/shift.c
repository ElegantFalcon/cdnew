#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char stack[50];
int top =-1;

struct Rule{
    char rhs[10];
    char lhs;
};

void push(char c){
    stack[++top] = c;
    stack[top+1] = '\0';
}

void pop(int n){
    top -= n;
    if(top<-1) top =-1;
    stack[top+1] = '\0';
}

int reduce(struct Rule rules[],int count){
    for(int i=0;i<count;i++){
        int len = strlen(rules[i].rhs);
        if(top+1 >= len){
            if(strncmp(&stack[top-len+1],rules[i].rhs,len) == 0){
                printf("REDUCE %s -> %c\n",rules[i].rhs,rules[i].lhs);
                pop(len-1);
                stack[top] = rules[i].lhs;
                stack[top+1] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

int  main(){
    char input[20];
    int i=0;
    printf("Enter the expression : ");
    scanf("%s",input);

    struct Rule rules[] = {
        {"i",'E'},
        {"E+E",'E'},
        {"E*E",'E'},
        {"(E)",'E'}
    };

    int count = sizeof(rules)/sizeof(rules[0]);

    stack[0] = '\0';
    char a = input[i];

    printf("\n STACK \t\t INPUT \t\t ACTION \n");

    while(a!='\0'){
        printf("%-10s \t%-10s \t SHIFT %c \n",stack,input+i,a);
        push(a);
        a = input[++i];
        while(reduce(rules,count));
    }

    while(reduce(rules,count));

    if(top == 0 && stack[top] == 'E'){
        printf("%-10s \t%-10s \t Accepted \n",stack,input+i);
    }

    else{
        printf("Parsing error");
    }

    return 0;
}