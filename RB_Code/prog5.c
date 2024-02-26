#include <stdio.h>
#include <wiringPi.h>

#define SWITCH_ON_PIN 19
#define SWITCH_OFF_PIN 20
#define LED_PIN 17

int main() {
    wiringPiSetupPhys();

    pinMode(SWITCH_ON_PIN, INPUT);
    pinMode(SWITCH_OFF_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    while (1) {
        if (digitalRead(SWITCH_ON_PIN) == HIGH) {
            digitalWrite(LED_PIN, HIGH);
        } else if (digitalRead(SWITCH_OFF_PIN) == HIGH) {
            digitalWrite(LED_PIN, LOW);
        }
    }

    return 0;
}

