#define F_CPU 16000000UL 

#include <avr/io.h> 
#include <util/delay.h>

#define InfraredPIN PD3
#define GREEN_LED PD4
#define ACTIVE_BUZZER PD5
#define DELAY_TIME 1000

void InfraredDetection () { 
    uint8_t ReceivingTube = (PIND & (1 << InfraredPIN)) ? 1 : 0;

    if (ReceivingTube == 0) {
        PORTD |= (1 << GREEN_LED) | (1 << ACTIVE_BUZZER);
        _delay_ms(DELAY_TIME);
        PORTD &= ~((1 << GREEN_LED) | (1 << ACTIVE_BUZZER));
    }
} 
int main () { 
    /* Set the infrared module as input, and enable pull-up resistor for it
    the green led as output,
    and the active buzzer as output */
    DDRD &= ~(1 << InfraredPIN);
    DDRD |= (1 << GREEN_LED) | (1 << ACTIVE_BUZZER);

    while (1) { InfraredDetection(); } 
    
    return 0; 
}

