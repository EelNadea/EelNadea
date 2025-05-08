.include "/usr/share/avra/m328Pdef.inc"

.org 0x0
	rjmp Initialize

.org 0x2				; INT0 vector
	rjmp INT0_ISR

INT0_ISR:
	eor r18, r17
	reti
	
Initialize:
	sei					; Enable global interrupt
	ldi r16, 0x1		
	ldi r17, 0x3
	out EIMSK, r16		; Enable INT0
	sts EICRA, r17 		; Rising edge interrupt
	ldi r16, 0x7		; Set LED's as outputs
	out DDRB, r16		; PB0, PB1, and PB2
	ldi r17, 0x1
	clr r18		

LOOP:
	sbrs r18, 0			; Skip if Bit in Register Set
	rjmp LOOP
	sbi PORTB, 0
	rcall DELAY
	sbi PORTB, 1
	cbi PORTB, 0
	rcall DELAY
	sbi PORTB, 2
    cbi PORTB, 1
    rcall DELAY
    cbi PORTB, 2
	rjmp LOOP

DELAY: 				
	ldi r20, 0x40
	
OLOOP:
	ldi r21, 0x50
	
MLOOP: 
	ldi r22, 0x50

ILOOP:
	dec r22
	brne ILOOP
	dec r21
	brne MLOOP
	dec r20
	brne OLOOP	
	ret
