#define F_CPU 16000000UL 

#include <avr/io.h> 
#include <util/delay.h> 

#define SoundSensorPIN PD5

#define GREEN_LED PB4 
#define YELLOW_LED PB3 
#define RED_LED PB2 

#define DELAY_TIME 70

void ToggleLED () { 
    PORTB ^= (1 << GREEN_LED); 
    _delay_ms(DELAY_TIME); 

    PORTB ^= (1 << YELLOW_LED); 
    _delay_ms(DELAY_TIME); 
    
    PORTB ^= (1 << RED_LED); 
    _delay_ms(DELAY_TIME); 
}

void SoundReceive () { 
    uint8_t sensorState = (PIND & (1 << SoundSensorPIN)) ? 1 : 0;

    if (sensorState == 1) { ToggleLED(); } 
} 
int main () { 
    // Set PD5 as input for the sound sensor. Set PB4, PB3, and PB2 as output 
    DDRD &= ~(1 << SoundSensorPIN); 
    DDRB |= (1 << GREEN_LED) | (1 << YELLOW_LED) | (1 << RED_LED); 

    while (1) { SoundReceive(); } 
    
    return 0; 
}