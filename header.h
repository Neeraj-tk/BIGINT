#ifndef BIGNUM
#define BIGNUM
#include<stdio.h>
 
typedef struct tag{
    int sign;  // 0 for positive and 1 for negative 
    int *data;
    int len; // number of digits in the bigint
} bignum;

//FUNCTION DECLARATIONS
void stringtobig(char* str,bignum* b);
void display(bignum *b);
void read(bignum *b);
int compare(bignum *b1,bignum *b2);
bignum* add(bignum *b1,bignum *b2);
void addition(bignum *b1,bignum *b2);
void subtraction(bignum *b1,bignum *b2);
void multiplication(bignum *b1,bignum *b2);
#endif

