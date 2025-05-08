.include "/usr/share/avra/m328Pdef.inc"

.org 0x0
	rjmp RESET

RESET:
	ldi r16, 0b111	; Set PB0, PB1, and PB2 as outputs
	out DDRB, r16

LOOP:
	sbi PORTB, 2	; PB2 ON
	rcall delay_1s
	cbi PORTB, 2	; PB2 OFF
	sbi PORTB, 1	; PB1 ON
	rcall delay_1s
	cbi PORTB, 1	; PB1 OFF
	sbi PORTB, 0	; PB0 ON
	rcall delay_1s
	cbi PORTB, 0	; PB0 OFF
	rjmp LOOP
		
delay_1s:
	ldi r18, 11		; Outer loop 

d1: ldi r19, 230	; Middle loop
d2: ldi r20, 255	; Inner loop

d3:
	dec r20
	brne d3
	dec r19
	brne d2
	dec r18
	brne d1
	ret
