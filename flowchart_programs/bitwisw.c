#include <stdio.h>

int main() {
    int number, n;

    // Input from the user
    printf("Enter a number: ");
    scanf("%d", &number);

    printf("Enter the value of n (bit position): ");
    scanf("%d", &n);

    // Check if n is valid (non-negative and within the size of an integer)
    if (n >= 0 && n < sizeof(int) * 8) {
        // Extract the nth bit using bitwise AND
        int nthBit = (number >> n) & 1;

        // Display the result
        printf("The %dth bit from the right in the binary representation of %d is: %d\n", n, number, nthBit);
    } else {
        printf("Invalid bit position. Please enter a non-negative integer less than %d.\n", sizeof(int) * 8);
    }

    return 0;
}

