#include <stdio.h>

int main() {
    // Example 3D array (2x3x4)
    int cube[4][3][4] = {
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
	   
        },
        {
            {13, 14, 15, 16},
            {17, 18, 19, 20},
            {21, 22, 23, 24}
        },
	{

	  {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
	},

	{

          {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        }


    };

    // Accessing elements and printing the cube
    printf("Cube:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++)
	

	    {
                printf("%d\t", cube[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}
