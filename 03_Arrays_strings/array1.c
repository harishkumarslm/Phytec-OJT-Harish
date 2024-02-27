#include<stdio.h>
int main()
{
	int arr[]={2,3,4,5,6,6,2,4};
	int len=sizeof(arr)/sizeof arr[0];
	int count;
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<i;j++)
		{
			if (arr[i]==arr[j])
			{
				printf("the %d duplicate element\n",arr[i]);
				count++;
			}
		}

	}




}
