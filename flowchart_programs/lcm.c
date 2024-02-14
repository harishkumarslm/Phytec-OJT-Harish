#include<stdio.h>
#include<math.h>
int main()
{
	int n,arr[10],mp,i,count;
	printf(" enter the  size for lcm");
	scanf("%d",&n);
	printf("enter the %d numbers for lcm ",n);
	for (i=0; i<n; i++)
		scanf("%d",&arr[i]);
	i=0;
	mp=arr[i];
	while(i<n)
	{
		if(mp<arr[i])
			mp = arr[i];
			i++;
	}

	while(1)
	{
		i=0;
		count=0;
		while(i<n)
		{
			if(mp%arr[i]==0)

				count++;
			i++;
		}
		if(count==n)
			break;
		else
			mp++;
	}
	 printf("\nLCM(");
   
    printf("%d = %d", arr[i], mp);
    return 0;
}


