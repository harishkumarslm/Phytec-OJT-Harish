#include<stdio.h>

int main()
{
    float a1,b1,c1,a2,b2,c2;
    printf("enter the a1,b1,c1:");
    scanf("%f %f %f",&a1,&b1,&c1);
    printf("enter the a2,b2,c2:");
    scanf("%f %f %f",&a2,&b2,&c2);
 

  if (a1*b2 == a2*b1) {
	  printf("the lines are parallel");
      }
    else {
        printf("the lines are not parallel");
    }

    return 0;
}
