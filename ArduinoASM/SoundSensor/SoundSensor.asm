.include "/usr/share/avra/m328Pdef.inc"

.org 0x0
	rjmp SETUP

SETUP:
	ldi r16, 0x20		; Set PB5 as output, and PB0 as input. 
	out DDRB, r16		; (PB5, Builtin LED) (PB0, Sound sensor)

TOGGLE_LED:
	sbis PINB, 0		; If PINB0 == 1, skip the next instruction
	rjmp TOGGLE_LED
	in r17, PORTB		; Read PORTB into r17
	eor r17, r16		; EOR == Exclusive OR
	out PORTB, r17
	rcall DEBOUNCE
	rjmp TOGGLE_LED
	
DEBOUNCE:				; ~0.1s delay at 16MHZ
	ldi r18, 0x1e

d1: ldi r19, 0xff
d2: ldi r20, 0xff

d3:
	dec r20
	brne d3
	dec r19
	brne d2
	dec r18
	brne d1
	ret
