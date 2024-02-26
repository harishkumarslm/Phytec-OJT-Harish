#include <stdio.h>
#include <wiringPi.h>

#define ROW_1 13
#define ROW_2 14
#define ROW_3 15
#define ROW_4 16
#define COLUMN_1 23
#define COLUMN_2 24
#define COLUMN_3 25
#define COLUMN_4 26

int main() {
    wiringPiSetupPhys();

    pinMode(ROW_1, INPUT);
    pinMode(ROW_2, INPUT);
    pinMode(ROW_3, INPUT);
    pinMode(ROW_4, INPUT);
    pinMode(COLUMN_1, OUTPUT);
    pinMode(COLUMN_2, OUTPUT);
    pinMode(COLUMN_3, OUTPUT);
    pinMode(COLUMN_4, OUTPUT);

    while (1) {
        if (digitalRead(ROW_1) == HIGH) {
            printf("Key '1' pressed\n");
        } else if (digitalRead(ROW_2) == HIGH) {
            printf("Key '2' pressed\n");
        } else if (digitalRead(ROW_3) == HIGH) {
            printf("Key '3' pressed\n");
        } else if (digitalRead(ROW_4) == HIGH) {
            printf("Key 'A' pressed\n");
        }

        delay(500);  // To avoid multiple detections for the same key press
    }

    return 0;
}

