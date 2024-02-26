#include <avr/io.h>
#include <util/delay.h>

void PWM_init() {
    TCCR1A |= (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
    DDRB |= (1 << PB1);
}

void set_servo_position(int degree) {
    OCR1A = 1000 + (degree * 11); // Adjust the values based on servo specifications
    _delay_ms(1000); // Wait for servo to reach the position
}

int main(void) {
    PWM_init();

    while (1) {
        set_servo_position(0);
        _delay_ms(1000);

        set_servo_position(90);
        _delay_ms(1000);

        set_servo_position(180);
        _delay_ms(1000);
    }

    return 0;
}

