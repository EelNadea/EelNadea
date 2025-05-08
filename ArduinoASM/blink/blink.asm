; Blink the Arduino Uno onboard LED (pin 13/PB5) every second
; Assemble: avra blink.asm
; Flash:    avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:blink.hex

.include "/usr/share/avra/m328Pdef.inc"

.org 0x0000
    rjmp RESET

RESET:
    ldi r16, (1 << PB5)     ; Set PB5 (digital 13) as output
    out DDRB, r16

LOOP:
    sbi PORTB, PB5      ; LED ON
    rcall delay_1s
    cbi PORTB, PB5      ; LED OFF
    rcall delay_1s
    rjmp LOOP

; ~1 second delay at 16 MHz (empirically tuned)
delay_1s:
    ldi r18, 61     ; Outer loop: 61

d1: ldi r19, 230    ; Middle loop: 230
d2: ldi r20, 255    ; Inner loop: 255

d3: dec r20
    brne d3
    dec r19
    brne d2
    dec r18
    brne d1
    ret
