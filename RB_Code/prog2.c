#include <stdio.h>
#include <wiringPi.h>

#define SWITCH_PIN 19
#define LED_PIN 20

int main() {
    wiringPiSetupPhys();
    
    pinMode(SWITCH_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    int switchState = LOW;

    while (1) {
        if (digitalRead(SWITCH_PIN) == HIGH) {
            switchState = !switchState;
            digitalWrite(LED_PIN, switchState);
            delay(500);
        }
    }

    return 0;
}

