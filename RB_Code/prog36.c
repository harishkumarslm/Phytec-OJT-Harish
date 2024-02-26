#include <stdio.h>
#include <wiringPi.h>

#define LM35_PIN 0 // Replace with the actual GPIO pin number

int main() {
    wiringPiSetup();

    while (1) {
        int adcValue = analogRead(LM35_PIN);

        // Convert ADC value to temperature in Celsius
        float temperature = (adcValue * 500.0) / 1024.0;

        printf("Temperature: %.2f°C\n", temperature);
        delay(1000); // Delay 1 second
    }

    return 0;
}

