#include <stdio.h>

int main() {
    int rows, cols;

    // Input the number of rows and columns from the user
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    // Ensure valid dimensions
    if (rows <= 0 || cols <= 0) {
        printf("Invalid dimensions. Please enter positive values for rows and columns.\n");
        return 1;  // Exit with an error code
    }

    // Declare the matrix with the given dimensions
    int matrix[rows][cols];

    // Input matrix elements from the user
    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("Enter element at position (%d, %d): ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }

    // Display the matrix
    printf("Matrix:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
