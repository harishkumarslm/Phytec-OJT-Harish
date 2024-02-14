#include <stdio.h>

int main() {
    // Number of red, black, and blue balls in the box
    int num_red = 3;
    int num_black = 5;
    int num_blue = 6;

    // Total number of balls in the box
    int total_balls = num_red + num_black + num_blue;

    // Calculate the probability of drawing 1 red, 1 black, and 1 blue ball
    double probability = (double)(num_red * num_black * num_blue) / 
                         (total_balls * (total_balls - 1) * (total_balls - 2));

    // Display the result
    printf("Probability of drawing 1 red, 1 black, and 1 blue ball: %.4lf\n", probability);

    return 0;
}

