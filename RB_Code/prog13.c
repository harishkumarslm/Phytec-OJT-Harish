#include <stdio.h>
#include <wiringPi.h>

#define ROW_1 13
#define ROW_2 14
#define ROW_3 15
#define ROW_4 16

int main() {
    wiringPiSetupPhys();

    pinMode(ROW_1, INPUT);
    pinMode(ROW_2, INPUT);
    pinMode(ROW_3, INPUT);
    pinMode(ROW_4, INPUT);

    while (1) {
        if (digitalRead(ROW_1) == HIGH) {
            printf("Key pressed in row-1\n");
        } else if (digitalRead(ROW_2) == HIGH) {
            printf("Key pressed in row-2\n");
        } else if (digitalRead(ROW_3) == HIGH) {
            printf("Key pressed in row-3\n");
        } else if (digitalRead(ROW_4) == HIGH) {
            printf("Key pressed in row-4\n");
        }

        delay(500);  // To avoid multiple detections for the same key press
    }

    return 0;
}

