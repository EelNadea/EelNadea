#include <avr/io.h>
#include <util/delay.h>

// Initialize the segments of the 7 segment display
const int a = PORTD2;
const int b = PORTD3;
const int c = PORTD4;
const int d = PORTD5;
const int e = PORTD6;
const int f = PORTD7;
const int g = PORTB0;

// Initialize the LED
const int led = PORTB3;
const unsigned long int led_delayTime = 100000UL;

// Delay time for countdown
const int DELAY_TIME = 16000;

void Draw9 () {
    // Turn on all segments (except segment e)
    PORTD |= (1 << a) | (1 << b) | (1 << c) | (1 << d) | (1 << f);
    PORTB |= (1 << g);
    _delay_ms(DELAY_TIME);
    // Turn off all
    PORTD &= ~((1 << a) | (1 << b) | (1 << c) | (1 << d) | (1 << f));
    PORTB &= ~(1 << g);
}

void Draw8 () {
    // Turn on all segments
    PORTD |= (1 << a) | (1 << b) | (1 << c) | (1 << d) | (1 << e) | (1 << f);
    PORTB |= (1 << g);
    _delay_ms(DELAY_TIME);
    // Turn off all
    PORTD &= ~((1 << a) | (1 << b) | (1 << c) | (1 << d) | (1 << e) | (1 << f));
    PORTB &= ~(1 << g);
}

void Draw7 () {
    // Turn on segments a, b, and c
    PORTD |= (1 << a) | (1 << b) | (1 << c);
    _delay_ms(DELAY_TIME);
    // Turn off all
    PORTD &= ~((1 << a) | (1 << b) | (1 << c));
}

void Draw6 () {
    // Turn on segments a, c, d, e, f, and g
    PORTD |= (1 << a) | (1 << c) | (1 << d) | (1 << e) | (1 << f);
    PORTB |= (1 << g);
    _delay_ms(DELAY_TIME);
    // Turn off all
    PORTD &= ~((1 << a) | (1 << c) | (1 << d) | (1 << e) | (1 << f));
    PORTB &= ~(1 << g);
}

void Draw5 () {
    // Turn on segments a, c, d, f, and g
    PORTD |= (1 << a) | (1 << c) | (1 << d) | (1 << f);
    PORTB |= (1 << g);
    _delay_ms(DELAY_TIME);
    // Turn off all
    PORTD &= ~((1 << a) | (1 << c) | (1 << d) | (1 << f));
    PORTB &= ~(1 << g);
}

void Draw4 () {
    // Turn on segments b, c, f, and g
    PORTD |= (1 << b) | (1 << c) | (1 << f);
    PORTB |= (1 << g);
    _delay_ms(DELAY_TIME);
    // Turn off all
    PORTD &= ~((1 << b) | (1 << c) | (1 << f));
    PORTB &= ~(1 << g);
}

void Draw3 () {
    // Turn on segments a, b, c, d, and g
    PORTD |= (1 << a) | (1 << b) | (1 << c) | (1 << d);
    PORTB |= (1 << g);
    _delay_ms(DELAY_TIME);
    // Turn off all
    PORTD &= ~((1 << a) | (1 << b) | (1 << c) | (1 << d));
    PORTB &= ~(1 << g);
}

void Draw2 () {
    // Turn on segments a, b, d, e, and g
    PORTD |= (1 << a) | (1 << b) | (1 << d) | (1 << e);
    PORTB |= (1 << g);
    _delay_ms(DELAY_TIME);
    // Turn off all
    PORTD &= ~((1 << a) | (1 << b) | (1 << d) | (1 << e));
    PORTB &= ~(1 << g);
}

void Draw1 () {
    // Turn on segments b and c
    PORTD |= (1 << b) | (1 << c);
    _delay_ms(DELAY_TIME);
    // Turn off all
    PORTD &= ~((1 << b) | (1 << c));
}

void Draw0 () {
    // Turn on all segments (except g) and the LED
    PORTD |= (1 << a) | (1 << b) | (1 << c) | (1 << d) | (1 << e) | (1 << f);
    PORTB |= (1 << led);
    _delay_ms(led_delayTime);
    // Turn off all
    PORTD &= ~((1 << a) | (1 << b) | (1 << c) | (1 << d) | (1 << e) | (1 << f));
    PORTB &= ~(1 << led);
}

int main () {
    // Set the segments and PortB3(LED) as outputs
    DDRD |= (1 << a) | (1 << b) | (1 << c) | (1 << d) | (1 << e) | (1 << f); 
    DDRB |= (1 << g) | (1 << led);

    while (1) {
        Draw9();
        Draw8();
        Draw7();
        Draw6();
        Draw5();
        Draw4();
        Draw3();
        Draw2();
        Draw1();
        Draw0();
    }

    return 0;
}