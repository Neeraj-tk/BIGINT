#include<stdio.h>
#include"header.h"
int main()
{
    bignum n1;
    bignum n2;
    read(&n1);
    read(&n2); 
    display(&n1);
    printf(" - ");
    display(&n2);
    printf(" = ");
    subtraction(&n1,&n2);
    printf("\n");
    display(&n1);
    printf(" + ");
    display(&n2);
    printf(" = ");
    addition(&n1,&n2);
    printf("\n");
    display(&n1);
    printf(" x ");
    display(&n2);
    printf(" = ");
    multiplication(&n1,&n2);
    
}