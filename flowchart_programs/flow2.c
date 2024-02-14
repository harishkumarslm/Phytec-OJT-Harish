#include<stdio.h>
int main()
{
	int a=1,b=2,count,range;
	printf("enter the range");
	scanf("%d",&range);
	while(count == range)
	{
		count=a+2;
		printf("%d",count);
		a=count;
	
		count=b+4;
		printf("%d",count);
		b=count;
	}
	return 0;

}
