#include<stdio.h>
int main()
{
int n, i, j;
printf("Enter the number of rows: ");
scanf("%d",&n);
for(i = 1; i <= n; i+=2)
{
for(j = 1; j <= i; j++)
{
printf("%d",j);
}
printf("\n");
}
return 0;
}
