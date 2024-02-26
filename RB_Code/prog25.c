#include <wiringPi.h>
#include <stdio.h>

int ir_sensor_pin = 0; // Replace with actual GPIO pin number

int main() {
    wiringPiSetup();

    pinMode(ir_sensor_pin, INPUT);

    while (1) {
        if (digitalRead(ir_sensor_pin) == HIGH) {
            printf("Obstacle detected\n");
        } else {
            printf("Obstacle not detected\n");
        }
        delay(1000); // Delay 1 second
    }

    return 0;
}

