#include <avr/io.h>
#include <util/delay.h>

void PWM_init() {
    TCCR1A |= (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
    DDRB |= (1 << PB1);
}

int main(void) {
    PWM_init();

    while (1) {
        for (int i = 0; i <= 255; i++) {
            OCR1A = i;
            _delay_ms(10);
        }

        _delay_ms(500);

        for (int i = 255; i >= 0; i--) {
            OCR1A = i;
            _delay_ms(10);
        }

        _delay_ms(500);
    }

    return 0;
}

