#include<stdio.h>
int main()
{
	int a =5,b = 10,c = 15,d=23,e=34;
	int *ptrarray[10]={&a,&b,&c,&d,&e};
	for(int i=0;i<5;i++)
	{
		printf("value of ptrarray[%d]=%p\n",i,ptrarray[i]);		
                printf("Value at *ptrarray[%d] = %d\n", i, *ptrarray[i]);
        }
return 0;
}

