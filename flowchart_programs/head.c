#include <stdio.h>
#include<math.h>

int main() {
    // Assuming fair coins with two possible outcomes (heads or tails)
    int total_outcomes = 2 * 2 * 2;  // 2 outcomes for each of the 3 coins
    int favorable_outcomes = 1;     // Only one favorable outcome: heads on all three coins

    // Calculate the probability
    double probability = (double)favorable_outcomes / total_outcomes;

    // Display the result
    printf("Probability of getting heads on all 3 coins: %.2lf\n", probability);

    return 0;
}


	
