#include <stdio.h>

int main() {
    int num1, num2, sum = 0;

    // Input two numbers from the user
    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    // Swap the numbers if the second number is smaller than the first
    if (num1 > num2) {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }

    // Calculate the sum of numbers not divisible by 5
    for (int i = num1; i < num2; i++) {
        if (i % 5 == 0) {
            num1++;
        }
	else 
	{
		sum=sum+num1;
		num1++;
	}
    }

    // Display the result
    printf("Sum of numbers between %d and %d (not divisible by 5): %d\n", num1, num2, sum);

    return 0;
}

