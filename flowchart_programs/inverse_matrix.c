#include<stdio.h>
int main()
{
    int m,n,i,j;
    double determinant;
    printf("Enter the number of rows and column: \n");
    scanf("%d %d",&m,&n);     //Matrix size declaration
    int a[m][n];
    printf("\nEnter the 9 elements of the matrix: \n");
    for(int i=0;i<m;i++)     //Matrix Elements initialization
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    printf("\nThe elements in the matrix are before inverse: \n");
    for(int i=0;i<m;i++)     //Print the elements in the matrix 
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
   for(i=0;i<m;i++)
      determinant = determinant + (a[0][i]*(a[1][(i+1)%3]*a[2][(i+2)%3] - a[1][(i+2)%3]*a[2][(i+1)%3]));

   printf("\nInverse of matrix is: \n\n");
   for(i=0;i<m;i++){
      for(j=0;j<n;j++)
           printf("%.2f\t",((a[(i+1)%3][(j+1)%3] * a[(i+2)%3][(j+2)%3]) - (a[(i+1)%3][(j+2)%3]*a[(i+2)%3][(j+1)%3]))/ determinant);
       printf("\n");
   }

   return 0;
}


