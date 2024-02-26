#include <stdio.h>
#include <wiringPi.h>

#define SOIL_PIN 0 // Replace with the actual GPIO pin number
#define MOTOR_PIN 2 // Replace with the actual GPIO pin number

int main() {
    wiringPiSetup();

    pinMode(SOIL_PIN, INPUT);
    pinMode(MOTOR_PIN, OUTPUT);

    while (1) {
        int soilValue = digitalRead(SOIL_PIN);

        if (soilValue == LOW) {
            digitalWrite(MOTOR_PIN, HIGH); // Turn on motor (LED) when water is not present
        } else {
            digitalWrite(MOTOR_PIN, LOW);  // Turn off motor (LED) when water is present
        }

        delay(1000); // Delay 1 second
    }

    return 0;
}

