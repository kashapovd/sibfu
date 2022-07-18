;
; work4.asm
;
; Created: 19.02.2022 15:49:16
; Author : Yaroslav
; var6
; task: blink if int0 is activated, stop blinking if int1 is activated, int0=falling, int1=rising

.def led=r20
.def enable_blink=r19
.def tmp=r16
.def loop_count=r18
.def iLoopRl=r24
.def iLoopRh=r25
.equ iVal=39998

.cseg
	.org 0x00
	rjmp reset
	.org 0x02
	rjmp process_int0
	.org 0x04
	rjmp process_int1

process_int0:
	ldi enable_blink, 0xFF
	reti

process_int1:
	ldi enable_blink, 0x00
	reti

reset:
	ldi tmp, LOW(RAMEND)
	out SPL, tmp
	ldi tmp, HIGH(RAMEND)
	out SPH, tmp
	sei
	ldi tmp, (1 << ISC01 | 1 << ISC11 | 1 << ISC10)
	out MCUCR, tmp
	ldi tmp, (1 << INT0 | 1 << INT1)
	out GICR, tmp
	out DDRD, tmp
	ser tmp
	out DDRB, tmp
 
blink:
	sbrs enable_blink, 0x00
	rjmp blink
	out PORTB, led
	com led
	ldi loop_count, 50 // 50*10 = 500ms delay
	rcall delay
	rjmp blink

delay:
	ldi	iLoopRl,LOW(iVal)
	ldi	iLoopRh,HIGH(iVal)

inner_loop:	
	sbiw iLoopRl,1
	brne inner_loop
	dec	loop_count
	brne delay
	nop
	ret