#include<stdio.h>
int main()
{       
        int hum,temp;
        int h=23,t=33;
        hum=(h%(1048576))*100;
        printf("%d  the humidity is\n",hum);
        temp=(t%(1048576))*150;
        printf("%d the temp is\n",temp);
        return 0;
}       
