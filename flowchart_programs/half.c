#include<stdio.h>
int main()
{
	int i=1,r,s,j;
	printf("enter the rows:");
	scanf("%d",&r);
	if (i<=r)
	{
	for (s=1;s<=r-i;i++)
	{
	printf(" ");
	s=s+1;
	}
	
	j=1;
	for (j=1;j<=(i*2)-1;j++)
	{
	printf("*");
	j=j+1;
	printf("\n");
	i=i+1;
	}
}
}
