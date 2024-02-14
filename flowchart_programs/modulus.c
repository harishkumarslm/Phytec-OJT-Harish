

// C Program to illustrate the working of modulo operator
#include <stdio.h>
 
int main(void)
{
    int x, y;
    int result;
    printf("enter the x value:");
    scanf("%d",&x);
    printf("enter the y value:");
    scanf("%d",&y);
    // using modulo operator
    result = x % y;
    printf("%d", result);
 
    result = y % x;
    printf("\n%d", result);
 
  
 
    return 0;
}
