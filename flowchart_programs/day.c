#include<stdio.h>
#include<math.h>
int main()
{
	int h,d,m,y,j,k;
	printf("enter the date month year:");
	scanf("%d %d %d",&d,&m,&y);
       if (m<3)
      { 
	      m +=12;
	      y--; 
      }


	
	k=y%100;
	j=y/100;

	h= (d +(13*(m+1)/5) +(k)+(k/4)+(j/4)-(2*j)) % 7;
	
        switch(h)

	{
	case 0:
                   printf("saturday\n");
                   break;
	case 1:
                   printf("sunday\n");
  		   break;
        case 2:
                   printf("monday\n");
                   break;
                case 3:
                   printf("tuesday\n");
                   break;
                case 4:
                   printf("wednesday\n");
                   break;
                case 5:
                   printf("thursday\n");
                   break;
                case 6:
                   printf("friday\n");
                   break;
}

return 0;
}



