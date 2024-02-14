#include<stdio.h>
int main()
{
	float v2,v,r1,r2,r3,r4,i2,v1,v3,p;
	printf("the voltage for v,v2:");
	scanf("%f %f",&v,&v2);
	printf("the resisatnce r1,r2,r3,r4:");
	scanf("%f %f %f %f",&r1,&r2,&r3,&r4);
	v2=((-r1+(v*r2)+(v*(r3+r4)))/3*v);
	v3=(v2/(r3+r4)*r4);
	p=(((v3)*(v3))/r4);
	printf("the voltage v3:%f v",v3);
	printf("the power:%f w",p);
	return 0;
}

