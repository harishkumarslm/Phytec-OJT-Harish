#include <stdio.h>
#include <math.h>

int main() {
    int start, end;

    // Input from the user
    printf("Enter the starting number: ");
    scanf("%d", &start);

    printf("Enter the ending number: ");
    scanf("%d", &end);

    // Find and display Armstrong numbers in the given range
    printf("Armstrong numbers between %d and %d are:\n", start, end);

    for (int i = start; i <= end; ++i) {
        int num = i;
        int originalNum = num;
        int remainder, result = 0, n = 0;

        // Count the number of digits
        while (originalNum != 0) {
            originalNum /= 10;
            ++n;
        }

        originalNum = num;

        // Calculate the result
        while (originalNum != 0) {
            remainder = originalNum % 10;
            result += pow(remainder, n);
            originalNum /= 10;
        }

        // Check if the number is Armstrong and display
        if (result == num) {
            printf("%d\n", num);
        }
    }

    return 0;
}

