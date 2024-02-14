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
	
		
	if (a>b)
	{
		printf(" a is greater than b\n\r ");
		if(a>c)
		{
			printf("a is greater than c \n\r");
		}
		else 
		{
			printf("c is greater than a\n\r");

			if (a>d)
			{
				printf("a is greater than d \n\r");
			}
			else 
			{
				printf("d is greater than a\n\r");
			}
		}
	}
	else 
	{
		printf("b is greater than a\n\r");

		if (b>c)
		{
			printf("b is greater than c\r\n");
			if (b>d)
			{

				printf("b is greater than d \r\n");
			}
			else 
			{
				printf("d is greater than b\r\n");
			}
		}
		else 
		{
			printf("c is greater than b\r\n");

			if (c>d)
			{
				printf("c is greater than d\r\n");
			}
			else 
			{
				printf("d is greater than c\r\n");
			}

		}

	}
}
	
