#define F_CPU 16000000UL // 16million

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define DHT11_PIN PB0
#define BLUE_LED PB1
#define DELAY_TIME 500

void StartSignal () {
    _delay_ms(2000); // Wait for 2s according to datasheet

    PORTB &= ~(1 << DHT11_PIN);
    _delay_ms(18);
    PORTB |= (1 << DHT11_PIN);
    _delay_us(20);

    DDRB &= ~(1 << DHT11_PIN);
}

bool CheckResponse () {
    uint16_t timeout = 0;
    DDRB &= ~(1 << DHT11_PIN);
    while ( !(PINB & (1 << DHT11_PIN)) ) { 
        if (++timeout > 1280) { return false; } // 1280 == 80us
    }

    timeout = 0;
    while ( (PINB & (1 << DHT11_PIN)) ) { 
        if (++timeout > 1280) { return false; } 
    }
    
    return true;
}

uint16_t MeasurePulseLength () {
    uint16_t timer = 0;
    while ( !(PINB & (1 << DHT11_PIN)) ) {
        if (++timer > 800) { return 0; } // 800 == 50us
    }

    timer = 0;
    while ( (PINB & (1 << DHT11_PIN)) ) {
        ++timer;
    }

    return timer;
}

void ReadData (bool *ResponseVerification, uint16_t *Humidity, uint16_t *Temperature, uint8_t *Checksum) {
    if (*ResponseVerification == true) {

        for (int a = 0; a < 16; a++) { // Humidity
            uint16_t pulseLength = MeasurePulseLength();
            *Humidity <<= 1;
            if (pulseLength > 896) { *Humidity |= 1; } // 896 == 56us
        }

        for (int b = 0; b < 16; b++) { // Temperature
            uint16_t pulseLength = MeasurePulseLength();
            *Temperature <<= 1;
            if (pulseLength > 896) { *Temperature |= 1; }
        }
        
        for (int c = 0; c < 8; c++) { // Checksum
            uint16_t pulseLength = MeasurePulseLength();
            *Checksum <<= 1;
            if (pulseLength > 896) { *Checksum |= 1; }
        }
    }
    else { return; }
}

bool CheckIfEqual (uint16_t *Humidity, uint16_t *Temperature, uint8_t *Checksum) {

    // Calculate checksum by summing high and low bytes of Humidity and Temperature
    uint8_t calculatedCheckSum = (*Humidity >> 8) + (*Humidity & 0xFF) +
                                 (*Temperature >> 8) + (*Temperature & 0xFF);

    if (calculatedCheckSum == *Checksum) { return true; }
    else { return false; }
}

int main () {
    uint16_t Humidity = 0;
    uint16_t Temperature = 0;
    uint8_t Checksum = 0;

    while (1) {
        DDRB |= (1 << DHT11_PIN) | (1 << BLUE_LED);
        PORTB |= (1 << DHT11_PIN); _delay_ms(500); // Idle state
        
        StartSignal();
        bool ResponseVerification = CheckResponse();
        ReadData(&ResponseVerification, &Humidity, &Temperature, &Checksum);

        bool IsEqual = CheckIfEqual(&Humidity, &Temperature, &Checksum);
        if (IsEqual == true) {
            uint16_t HumidInt = Humidity >> 8; // Extract the integer part
            uint16_t TempInt = Temperature >> 8; 
            if (TempInt >= 1 || HumidInt >= 1) { 
                PORTB |= (1 << BLUE_LED);
                _delay_ms(DELAY_TIME);
                PORTB &= ~(1 << BLUE_LED);
            }
        }
    }
    
    return 0;
}