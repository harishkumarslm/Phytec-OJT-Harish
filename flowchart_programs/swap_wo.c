#include<stdio.h>
int main()
{
   int a=20,b=30;
   printf("before swap: %d %d ",a,b);
   a=a+b;
   b=a-b;
   a=a-b;
   printf("after  swap: %d %d",a,b);
}


