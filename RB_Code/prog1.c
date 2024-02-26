#include <stdio.h>
#include <wiringPi.h>

#define SWITCH_PIN 19
#define LED_PIN 20

int main() {
    wiringPiSetupPhys();
    
    pinMode(SWITCH_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    while (1) {
        if (digitalRead(SWITCH_PIN) == HIGH) {
            digitalWrite(LED_PIN, HIGH);
        } else {
            digitalWrite(LED_PIN, LOW);
        }
    }

    return 0;
}

