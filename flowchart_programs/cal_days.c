#include <stdio.h>
#include <time.h>

int main() {
    int h1, m1;
    int place;
    
    printf("Enter the Indian Railway time hh:mm: ");
    scanf("%d %d", &h1, &m1);

    printf("Please enter the place to display:\n");
    printf("1 for London\n");
    printf("2 for America\n");
    scanf("%d", &place);

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    switch (place) {
        case 1:
            timeinfo->tm_hour = h1;
            timeinfo->tm_min = m1;
            mktime(timeinfo);  // Normalize the time structure

            // Add 5 hours and 30 minutes to convert to London time
            timeinfo->tm_hour -= 5;
            timeinfo->tm_min -= 30;

            printf("The London UK time zone hh:mm: %02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);

            if (timeinfo->tm_hour >= 12) {
                printf(" pm");
            } else {
                printf(" am");
            }
            break;
	  case 2:
	    timeinfo->tm_hour = h1;
            timeinfo->tm_min = m1;
            mktime(timeinfo);  // Normalize the time structure

            // Add 10 hours and 30 minutes to convert to London time
            timeinfo->tm_hour -= 10;
            timeinfo->tm_min -= 30;

            printf("The London UK time zone hh:mm: %02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);

            if (timeinfo->tm_hour >= 12) {
                printf(" pm");
            } else {
                printf(" am");
            }
            break;

        default:
            printf("Invalid choice\n");
    }

    return 0;
}

