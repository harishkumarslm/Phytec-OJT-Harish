#include <stdio.h>
#include <wiringPi.h>

#define SWITCH_PIN 12
#define LED_PIN 13

int main() {
    wiringPiSetupPhys();

    pinMode(SWITCH_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    int switchCount = 0;

    while (1) {
        if (digitalRead(SWITCH_PIN) == HIGH) {
            switchCount++;
            for (int i = 0; i < switchCount; i++) {
                digitalWrite(LED_PIN, HIGH);
                delay(500);
                digitalWrite(LED_PIN, LOW);
                delay(500);
            }
            delay(500);
        }
    }

    return 0;
}

