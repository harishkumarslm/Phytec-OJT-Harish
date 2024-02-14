#include<stdio.h>
int main()
{
	float fah,cel;
	printf("enter the fahrenheit:");
	scanf("%f",&fah);
	cel=(fah-32)*0.5556;
	printf("the celsiusis :%f c",cel);
	return 0;
}
