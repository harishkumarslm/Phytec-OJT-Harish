#include <avr/io.h>
#include <util/delay.h>

void PWM_init() {
    TCCR1A |= (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
    DDRB |= (1 << PB1);
}

int read_pot() {
    // Implement the code to read the potentiometer value
    // This may involve using ADC and appropriate configuration
    // Return a value between 0 and 180 (degrees) based on pot position
}

void set_servo_position(int degree) {
    OCR1A = 1000 + (degree * 11); // Adjust the values based on servo specifications
    _delay_ms(1000); // Wait for servo to reach the position
}

int main(void) {
    PWM_init();

    while (1) {
        int pot_value = read_pot();
        int servo_position = (pot_value * 180) / 1024; // Adjust based on ADC resolution
        set_servo_position(servo_position);
    }

    return 0;
}

