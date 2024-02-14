#include <stdio.h>
int main()
{
    int m,n;
    printf("Enter the number of rows and column: \n");
    scanf("%d %d",&m,&n);     //Matrix size declaration
    int a[m][n];
    printf("\nEnter the 9 9 9 9 9 9 9 9 9 elements of the matrix: \n");
    for(int i=0;i<m;i++)     //Matrix Elements initialization
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    printf("\nThe elements in the matrix are: \n");
    for(int i=0;i<m;i++)     //Print the elements in the matrix 
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    int lsum=0;        //Declare a variable to calculate lower triangular sum
    if(m==n)          //Check whether number of rows and column are equal or not
    {
       for(int i=0;i<m;i++)
       {
          for(int j=0;j<n;j++)
          {
               if(i>=j)     //Iterate only through the lower triangular elements
               lsum=lsum+a[i][j];   //Calculate the sum
          }
        }
        printf("\nThe sum of lower triangular matrix is %d",lsum);   //Display the sum
    }
    else
    {
        printf("Not Possible to display lower triangular elements sum");   //if number of rows and column are not equal
    }
    return 0;
}
