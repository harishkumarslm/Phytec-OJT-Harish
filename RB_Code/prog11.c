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
            if (switchCount % 2 != 0) {
                digitalWrite(LED_PIN_1, HIGH);
                digitalWrite(LED_PIN_2, LOW);
                printf("Switch Pressed %d times - LED1 ON, LED2 OFF\n", switchCount);
            } else {
                digitalWrite(LED_PIN_1, LOW);
                digitalWrite(LED_PIN_2, HIGH);
                printf("Switch Pressed %d times - LED1 OFF, LED2 ON\n", switchCount);
            }
            delay(500);
        }
    }

    return 0;
}

