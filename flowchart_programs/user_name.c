#include<stdio.h>
void fun1(int num1 ,int num2,int num)
{
	double result;
	int swap;
	printf("enter the 0 for addition\r\n");
	printf("enter the 1 for subtraction\r\n");
	printf("enter the 2 for multiplication\r\n");
	printf("enter the 3 for division\r\n");
	printf("enter the 4 for mos]dulus\r\n");
	printf("enter the number (0-4) process:\r\n");
	scanf("%d",&num);

	switch (num)
	{

	case 0:
	result=num1+num2;
	printf("the addition:%lf",result);
	break;

	case 1:
	 
	result=num1-num2;
	printf("the subtraction:%lf",result);
	break;

	case 2:
	 
	result=num1*num2;
	printf("the multiplication:%lf",result);
	break;

	case 3:
	if (num2 !=0)
	{
	result=num1/num2;
	printf("the division:%lf",result);
	break;
	}
	else if(num2>num1)
	{
		result=num2/num1;
		printf("the dividion:-%lf",result);
	}
	else 
	{
		printf("not process division");
	}
	break;
        case 4:
	result =num1%num2;
        printf("the before swap modulus:%lf\r\n",result);

	if(num2>num1)
	{
		swap=num1;
		num1=num2;
		num2=swap;
	}
        result =num1%num2;
        printf("the after swap modulus:%lf\r\n",result);
        break;
	default:
	   printf("invalid operation\n");
	  }

}
int main()
{
	int num1,num2,result;
        printf("enter the number1:");
        scanf("%d",&num1);
        printf("enter the number2:");
        scanf("%d",&num2);
	fun1(num1,num2,result);
	return 0;
}
