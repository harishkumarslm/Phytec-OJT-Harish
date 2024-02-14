#include<stdio.h>
int main()
{
	int arr[]={1,2,3,4,5};
	int medium,low,high,size;
	low=0;
	high=size-1;
	medium=((low+high)/2);
			
	printf("the medium %d element\n",medium);
		
	if(medium>high)
	{
		low=medium+1;
		printf("the next number%d/n",low);
	}
	else
	{
		high=medium-1;
		printf("the previous number%d/n",high);

	}

	return 1;
}

