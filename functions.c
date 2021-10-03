#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"header.h"
void stringtobig(char* str,bignum* b)   //function to convert string into bigint
{
    //Checking if number is positive or negative
    int i,k;
    //assigning sign for the number
    if(str[0]=='-')
    {
        b->sign=1;
        i=1;
    }
    else
    {
        b->sign=0;
        i=0;
    }
    //skipping leading zeroes
    while(str[i]=='0')
    {
        i++;
    }
    b->len=strlen(str)-i;
    b->data=(int*)malloc(sizeof(int)*(b->len));
    k=b->len-1;
    while(str[i]!='\0')
    {
        b->data[k]=str[i]-'0';
        i++;
        k--;
    }
    if(b->len==0) //when the number entered by user is zero
    {
        b->len=1;
        b->data[0]=0;
    }
}

void display(bignum *b)  //function to display bigint
{
    int i;
    if(b->sign!=0)
    {
        printf("-");
    }
    for(i=b->len-1;i>=0;i--)
    {
        printf("%d",b->data[i]);
    }
}
void read(bignum *b)  //function to read bigint as a string
{
    char str[309];  
    printf("Enter the Big Integer :");
    scanf("%s",str);
    stringtobig(str,b);
}
int compare(bignum *b1,bignum *b2)  //function to compare two bigint numbers
{
    int i,retval;
    if(b1->len==b2->len)
    {
        i=b1->len-1;
        while(i>=0 && b1->data[i]==b2->data[i])
        {
            i--;
        }
        if(i==-1)
        {
            retval=0;
        }
        else
        {
            retval=b1->data[i]-b2->data[i];
        }
    }
    else
    {
        retval=b1->len-b2->len;
    }
    return retval;
}
bignum* add(bignum *b1,bignum *b2)  
{
    int carry,i,j,sum,k;
    bignum *ans=(bignum*)malloc(sizeof(bignum));
    if(b1->len==b2->len)
    {
        ans->len=b1->len+1;
    }
    else
    {
        ans->len=(b1->len)>(b2->len)?(b1->len)+1:(b2->len)+1;
    }
    ans->data=(int*)malloc(sizeof(int)*(ans->len));
    i=0;
    j=0;
    k=0;
    carry=0;
    while(i<b1->len || j<b2->len || carry!=0)
    {
        if(i< b1->len && j< b2->len) 
        {
            sum=b1->data[i]+b2->data[j];
        }
        else if(i<b1->len)
        {
            sum=b1->data[i];
        }
        else if(j< b2->len)
        {
            sum=b2->data[j];
        }
        else
        {
            sum=0;
        }
        sum+=carry;
        carry=sum/10;
        ans->data[k]=sum%10;
        k++;
        i++;
        j++;
    }
    ans->len=k;
    return ans;
}
bignum* sub(bignum *b1,bignum *b2)
{
    int borrow,i,j,diff,k;
    bignum *ans=(bignum*)malloc(sizeof(bignum));
    if(b1->len==b2->len)
    {
        ans->len=b1->len;
    }
    else
    {
        ans->len=(b1->len)>(b2->len)?(b1->len):(b2->len);
    }
    ans->data=(int*)malloc(sizeof(int)*ans->len);
    i=0;
    j=0;
    k=0;
    borrow=0;
    while(i<b1->len)
    {
        if(i< b1->len && j< b2->len) 
        {
            diff=b1->data[i]-b2->data[j]-borrow;
        }
        else if(i<b1->len)
        {
            diff=b1->data[i]-borrow;
        }
        if(diff<0)
        {
            diff+=10;
            borrow=1;
        }
        else
        {
            borrow=0;
        }
        ans->data[k]=diff;
        k++;
        i++;
        j++;
    }
    if(ans->data[k-1]==0)
    {
        ans->len=k-1;
    }
    else
    {
        ans->len=k;
    }
    return ans;
}
void addition(bignum *b1,bignum *b2)  //function to perform addition operation
{
    bignum *ans;
    if(b1->sign==b2->sign)
    {
       ans=add(b1,b2);
       ans->sign=b1->sign;
       display(ans);
    }
    else
    {
        if(compare(b1,b2)>0)
        {
            ans=sub(b1,b2);
            ans->sign=b1->sign;
        }
        else
        {
            ans=sub(b2,b1);
            ans->sign=b2->sign;
        }
        display(ans);
    }
}
void subtraction(bignum *b1,bignum *b2)  //function to perform subtraction operation
{
    if(b2->sign==0)
    {
        b2->sign=1;
    }
    else
    {
        b2->sign=0;
    }
    addition(b1,b2);
    if(b2->sign==0)
    {
        b2->sign=1;
    }
    else
    {
        b2->sign=0;
    }

}
void multiplication(bignum *b1,bignum *b2)  //function to perform multiplication operation
{
    int i,j,carry,prod,sum,temp;
    bignum *ans=(bignum*)malloc(sizeof(bignum));
    ans->len=b1->len+b2->len;
    ans->data=(int*)malloc(sizeof(int)*ans->len);
    for(i=0;i<ans->len;i++)
    {
        ans->data[i]=0;
    }
    for(i=0;i<b1->len;i++)
    {
        carry=0;
        for(j=0;j<b2->len;j++)
        {
            prod=b1->data[i]*b2->data[j];
            sum=prod+carry;
            ans->data[i+j]+=sum;
            carry=ans->data[i+j]/10;
            ans->data[i+j]=ans->data[i+j]%10;
        }
        if(carry!=0)
        {
            ans->data[i+j]+=carry;
            if(ans->data[i+j]>9)
            {
                ans->data[i+j]=(ans->data[i+j])%10;
                ans->data[i+j+1]+=(ans->data[i+j])/10;
            }

        }
    }
    i=ans->len-1;
    while(ans->data[i]==0 && i>=0)
    {
        i--;
    }
    ans->len=i+1;
    if(ans->len==0) //when the number entered by user is zero
    {
        ans->len=1;
        ans->data[0]=0;
    }
    if(b1->sign==b2->sign)
    {
        ans->sign=0;
    }
    else
    {
        ans->sign=1;
    }
    display(ans);
}