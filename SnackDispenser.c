#define F_CPU 16000000UL // 16 million

#include <avr/io.h>
#include <util/delay.h>

#define SG90_PIN PB1
#define INFRARED_PIN PB0

void RotateLow () {
    PORTB |= (1 << SG90_PIN);
    _delay_us(1000);
    PORTB &= ~(1 << SG90_PIN);
    _delay_ms(20);
}

void RotateHigh () {
    PORTB |= (1 << SG90_PIN);
    _delay_us(2000);
    PORTB &= ~(1 << SG90_PIN);
    _delay_ms(20);
}

int main () {
    DDRB |= (1 << SG90_PIN);
    DDRB &= ~(1 << INFRARED_PIN);
    PORTB |= (1 << INFRARED_PIN);
    
    while (1) {
        if ( !(PINB & (1 << INFRARED_PIN)) ) { RotateLow(); }
        else { RotateHigh(); }
    }

    return 0;
}