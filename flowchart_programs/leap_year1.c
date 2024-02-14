#include<stdio.h>

int main() {
    int start_year, end_year, leap_count = 0, non_leap_count = 0;

    printf("Enter the starting year: ");
    scanf("%d", &start_year);

    printf("Enter the ending year: ");
    scanf("%d", &end_year);

    for (int year = start_year; year <= end_year; year++) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            leap_count++;
        } else {
            non_leap_count++;
        }
    }

    printf("Number of leap years: %d\n", leap_count);
    printf("Number of non-leap years: %d\n", non_leap_count);

    return 0;
}

