#include <wiringPi.h>
#include <stdio.h>

int trig_pin = 0; // Replace with actual GPIO pin number
int echo_pin = 1; // Replace with actual GPIO pin number

int main() {
    wiringPiSetup();

    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);

    while (1) {
        digitalWrite(trig_pin, LOW);
        delayMicroseconds(2);
        digitalWrite(trig_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig_pin, LOW);

        while (digitalRead(echo_pin) == 0);
        long startTime = micros();

        while (digitalRead(echo_pin) == 1);
        long travelTime = micros() - startTime;

        int distance = travelTime / 58; // Speed of sound is 343 meters per second, and 1 microsecond is 1/1000000 seconds. Divide by 2 for round trip.

        printf("Distance: %d cm\n", distance);
        delay(1000); // Delay 1 second
    }

    return 0;
}

