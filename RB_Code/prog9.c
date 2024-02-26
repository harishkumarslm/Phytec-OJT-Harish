#include <stdio.h>
#include <wiringPi.h>

#define SWITCH_PIN 12
#define LED_PIN_1 13
#define LED_PIN_2 17

int main() {
    wiringPiSetupPhys();

    pinMode(SWITCH_PIN, INPUT);
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);

    int switchCount = 0;

    while (1) {
        if (digitalRead(SWITCH_PIN) == HIGH) {
            switchCount++;
            for (int i = 0; i < switchCount; i++) {
                digitalWrite(LED_PIN_1, HIGH);
                delay(500);
                digitalWrite(LED_PIN_1, LOW);
                delay(500);
            }
            delay(500);
            for (int i = 0; i < switchCount * 3; i++) {
                digitalWrite(LED_PIN_2, HIGH);
                delay(500);
                digitalWrite(LED_PIN_2, LOW);
                delay(500);
            }
            delay(500);
        }
    }

    return 0;
}

