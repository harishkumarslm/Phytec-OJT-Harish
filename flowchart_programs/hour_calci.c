#include<stdio.h>
int main()
{
	int s,hour,minute,second;
        printf("enter the second:");
	scanf("%d",&s);
	hour=s/3600;
	minute=(s%3600)/60;
	second=s%60;
	printf("enter seconds in hour:minute:second %d:%d:%d",hour,minute,second);
}
