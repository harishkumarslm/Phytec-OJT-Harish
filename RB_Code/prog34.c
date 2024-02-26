#include <stdio.h>
#include <wiringPi.h>

#define LDR_PIN 0 // Replace with the actual GPIO pin number
#define LED_PIN 2 // Replace with the actual GPIO pin number

int main() {
    wiringPiSetup();

    pinMode(LDR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    while (1) {
        int ldrValue = digitalRead(LDR_PIN);

        if (ldrValue == LOW) {
            digitalWrite(LED_PIN, HIGH); // Turn on LED in the dark
        } else {
            digitalWrite(LED_PIN, LOW);  // Turn off LED in light
        }

        delay(1000); // Delay 1 second
    }

    return 0;
}

