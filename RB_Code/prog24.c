#include <wiringPi.h>

int segment_pins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // Replace with actual GPIO pin numbers

void displayNumber(int num) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(segment_pins[i], (num & (1 << i)) ? HIGH : LOW);
    }
}

int main() {
    wiringPiSetup();

    for (int i = 0; i < 8; i++) {
        pinMode(segment_pins[i], OUTPUT);
    }

    while (1) {
        for (int i = 0; i < 10; i++) {
            displayNumber(i);
            delay(1000); // Delay 1 second
        }
    }

    return 0;
}

