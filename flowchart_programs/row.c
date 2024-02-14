#include <stdio.h>

int main() {
    int i, j, n,r=100;
    
    printf("\nEnter the value: ");
    scanf("%d", &n);

    // Printing the upper half of the pattern
    for (i = 1; i <= n; i++) {
        printf("\n");
        for (j = 1; j <= (n - i); j++) {
            printf("   ");
        }
        for (j = 1; j <= i; j++) {
            printf(" %2d", j);
        }
        for (j = i - 1; j >= 1; j--) {
            printf(" %2d", j);
        }
    }


    return 0;
}

