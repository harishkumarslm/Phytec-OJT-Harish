#include <stdio.h>
#include <wiringPi.h>

#define SWITCH_PIN 12
#define LED_PIN_1 13
#define LED_PIN_2 17
#define LED_PIN_3 19

int main() {
    wiringPiSetupPhys();

    pinMode(SWITCH_PIN, INPUT);
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
    pinMode(LED_PIN_3, OUTPUT);

    int switchCount = 0;

    while (1) {
        if (digitalRead(SWITCH_PIN) == HIGH) {
            switchCount++;
            switch (switchCount) {
                case 1:
                    digitalWrite(LED_PIN_1, HIGH);
                    break;
                case 2:
                    digitalWrite(LED_PIN_2, HIGH);
                    break;
                case 3:
                    digitalWrite(LED_PIN_3, HIGH);
                    break;
            }
            delay(500);
        }
    }

    return 0;
}

