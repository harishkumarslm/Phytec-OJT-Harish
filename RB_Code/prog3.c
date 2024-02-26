#include <stdio.h>
#include <wiringPi.h>

#define SWITCH_PIN_1 19
#define SWITCH_PIN_2 20
#define SWITCH_PIN_3 30
#define LED_PIN_1 13
#define LED_PIN_2 17
#define LED_PIN_3 19

int main() {
    wiringPiSetupPhys();

    pinMode(SWITCH_PIN_1, INPUT);
    pinMode(SWITCH_PIN_2, INPUT);
    pinMode(SWITCH_PIN_3, INPUT);
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
    pinMode(LED_PIN_3, OUTPUT);

    while (1) {
        if (digitalRead(SWITCH_PIN_1) == HIGH) {
            digitalWrite(LED_PIN_1, HIGH);
            delay(500);
            digitalWrite(LED_PIN_1, LOW);
        } else if (digitalRead(SWITCH_PIN_2) == HIGH) {
            digitalWrite(LED_PIN_2, HIGH);
            delay(500);
            digitalWrite(LED_PIN_2, LOW);
        } else if (digitalRead(SWITCH_PIN_3) == HIGH) {
            digitalWrite(LED_PIN_3, HIGH);
            delay(500);
            digitalWrite(LED_PIN_3, LOW);
        }
    }

    return 0;
}

