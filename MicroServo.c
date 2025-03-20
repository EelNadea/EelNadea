#define F_CPU 16000000UL // 16million

#include <avr/io.h>
#include <util/delay.h>

#define MICROSERVO_PIN PB4
#define TIMER 8

void DelayUS (int pulseWidth) {
    for (int a = 0; a < pulseWidth; a++) {
        _delay_us(1);
    }
}

void Angle_MinToMax () {
    for (int b = 400; b <= 1700; b += 50) {
        for (int c = 0; c < TIMER; c++) {
            PORTB |= (1 << MICROSERVO_PIN);
            DelayUS(b);
            PORTB &= ~(1 << MICROSERVO_PIN);
            _delay_ms(20);
        }
    }
}

void Angle_MaxToMin () {
    for (int d = 1650; d >= 450; d -= 50) {
        for (int e = 0; e < TIMER; e++) {
            PORTB |= (1 << MICROSERVO_PIN);
            DelayUS(d);
            PORTB &= ~(1 << MICROSERVO_PIN);
            _delay_ms(20);
        }
    }
}

int main () {
    DDRB |= (1 << MICROSERVO_PIN);

    while (1) {
        Angle_MinToMax();
        Angle_MaxToMin();
    }

    return 0;
}