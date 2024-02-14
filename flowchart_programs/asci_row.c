#include<stdio.h>

int main() {
    int i, j, a;

    printf("\nEnter the value: ");
    scanf("%d", &a);

    for (i = 1; i <= a; i++) {
        printf("\n");
        for (j = a - i + 1; j > 0; j--) {
            printf("%c", 'A'+(j-1));
        }
    }

    return 0;
}

