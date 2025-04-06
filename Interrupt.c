#define F_CPU 16000000UL // 16million

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLUE_LED PB3
#define GREEN_LED PB2
#define YELLOW_LED PB1 
#define RED_LED PB0
#define DELAY_TIME 75

volatile uint8_t LEDrunning = 0;

void InitializeInterrupt() {
    sei();
    EIMSK = (1 << INT0);

    // The rising edge of INT0 generates an interrupt request.
    EICRA = (1 << ISC01) | (1 << ISC00);
}

ISR(INT0_vect) {
    LEDrunning = !LEDrunning;
    _delay_ms(1);
}

int main() {
    DDRB = 0b1111; // Set LED's as outputs
    InitializeInterrupt();

    while (1) {
        if (LEDrunning == 1) {
            PORTB ^= (1 << BLUE_LED);
            _delay_ms(DELAY_TIME);
            PORTB ^= (1 << BLUE_LED) | (1 << GREEN_LED);
            _delay_ms(DELAY_TIME);
            PORTB ^= (1 << GREEN_LED) | (1 << YELLOW_LED);
            _delay_ms(DELAY_TIME);
            PORTB ^= (1 << YELLOW_LED) | (1 << RED_LED);
            _delay_ms(DELAY_TIME);
            PORTB ^= (1 << RED_LED);
        }
    }

    return 0;
}