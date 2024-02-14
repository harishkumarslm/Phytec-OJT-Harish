#include <stdio.h>
#include <ctype.h>

int main() {
    char str[100];
    int vowels = 0, consonants = 0, i;

    // Input a string from the user
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Iterate through each character in the string
    for (i = 0; str[i] != '\0'; i++) {
        // Check if the current character is an alphabet letter
        if (isalpha(str[i])) {
            // Convert the character to lowercase for easier comparison
            char lowercaseChar = tolower(str[i]);

            // Check if the lowercase character is a vowel
            if (lowercaseChar == 'a' || lowercaseChar == 'e' || lowercaseChar == 'i' ||
                lowercaseChar == 'o' || lowercaseChar == 'u') {
                vowels++;
            } else {
                consonants++;
            }
        }
    }

    // Display the results
    printf("Number of vowels: %d\n", vowels);
    printf("Number of consonants: %d\n", consonants);

    return 0;
}

