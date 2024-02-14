#include<stdio.h>

int main() {
    int i = 1, r, s, j,h=1;

    printf("Enter the rows: ");
    scanf("%d", &r);
//upper pyramid

    while (i <= r) {
        s = 1;

        while (s <= r - i) {
            printf("  ");
            s = s + 1;
        }

        j = 1;


        while (j <= (i * 2) - 1) {
            printf("%d ",h);
            j = j + 1;
	    h++;
        }
        printf("\n");
        i = i + 1;
    }
 // Lower Pyramid
    i = r - 1;  // Start from the second-to-last row for the lower pyramid

    while (i >= 1) {
        s = 1;

        // Print spaces
        while (s <= r - i) {
            printf(" ");

            s = s + 1;
        }

        j = 1;

        // Print stars
        while (j <= (i * 2) - 1) {
            printf("%d",h);
            j = j + 1;
	    h++;
        }

        printf("\n");
        i = i - 1;
    }

    return 0;
}

