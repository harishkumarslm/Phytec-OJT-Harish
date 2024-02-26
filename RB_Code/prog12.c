#include <stdio.h>
#include <wiringPi.h>

#define ROW_1 13
#define COLUMN_1 23

int main() {
    wiringPiSetupPhys();

    pinMode(ROW_1, INPUT);
    pinMode(COLUMN_1, OUTPUT);

    while (1) {
        if (digitalRead(ROW_1) == HIGH) {
            printf("Key pressed in row-1\n");
            delay(500);  // To avoid multiple detections for the same key press
        }
    }

    return 0;
}

