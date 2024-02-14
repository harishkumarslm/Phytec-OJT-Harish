#include<stdio.h>
int main()
{
	int a,b,c,d,r1,r2;
	printf("enter the a ,b ,c ,d :");
	scanf("%d %d %d %d",&a,&b,&c,&d);
	printf("%d+i%d of first complex number\r\n",a,b);
	printf("%d+i%d  of second complex number\r\n",d,c);
	r1=((a*c)+(b*d)/(c*c)+(d*d));
	r2=((b*c)-(a*d)/(c*c)+(d*d));
	printf("the real and imaginary values of two complex number:%d+i%d\r\n",r1,r2);
}
