#include <stdio.h>

int main() {
    int i, j, k, r;

    printf("Enter the number of rows: ");
    scanf("%d", &r);

    // Upper pyramid
    for (i = 1; i <= r; i++) {
        // Print leading spaces
        for (k = 1; k <= r - i; k++) {
            printf("  ");
        }

        // Print increasing numbers
        for (j = i; j <= 2 * i - 1; j++) {
            printf("%d", j);
            if (j < 2 * i - 1) {
                printf(" ");
            }
        }

        // Print decreasing numbers
        for (j = 2 * i - 2; j >= i; j--) {
            printf(" %d", j);
        }

        printf("\n");
    }

    return 0;
}

