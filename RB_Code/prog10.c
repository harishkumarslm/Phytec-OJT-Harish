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
            if (switchCount % 2 != 0) {
                digitalWrite(LED_PIN, HIGH);
                printf("LED ON\n");
            } else {
                digitalWrite(LED_PIN, LOW);
                printf("LED OFF\n");
            }
            delay(500);
        }
    }

    return 0;
}

