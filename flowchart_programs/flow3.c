#include<stdio.h>
int main()
{
	int a,b,c,d;
	printf("enter the number a:");
	scanf("%d",&a);
	printf("enter the number b:");
	scanf("%d",&b);
	printf("enter the number c:");
	scanf("%d",&c);
	printf("enter the number d:");
	scanf("%d",&d);
	if (a>b&&a>c&&a>d)
	{
		printf("a is greater than all b,c,d");

	}
	else if(b>c&&b>d&&b>a)
	{
		printf("b is greater than all a,c,d");
	}
	else if (c>a&&c>b&&c>d)
	{
		printf("c is greater than all a,d,d");

	}
	else 
	{
		printf("d is greater than all a,b,c");
	}
	return 0;
}

