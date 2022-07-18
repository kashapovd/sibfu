; Replace with your application code
;
; work7.asm
;
; Created: 27.05.2022 06:20:0
; Author: Yaroslav

.dseg
	 .equ digits_size=18
	 .org 0xA0
	 digits: .byte digits_size

	 .def rmode=r23
	 .def leds=r22
	 .def tmp=r21
	 
.cseg
	 .org 0x00
	 rjmp init
	 .org 0x02
	 rjmp button_int0
	 .org 0x04
	 rjmp button_int1
	 .org OVF0addr
	 rjmp timer0_ovf
	 .org ADCCaddr
	 rjmp adc_int
	 
init:	
	 sei
	 ldi tmp, (1<<TOIE0)
	 out TIMSK, tmp
	 clr tmp
	 out TCCR0, tmp
	 ldi tmp, (1 << ISC01 | 1 << ISC11)
	 out MCUCR, tmp
	 ldi tmp, (1 << INT0 | 1 << INT1)
	 out GICR, tmp
	 in tmp, DDRA
	 andi tmp, ~(1<<7)
	 out DDRA, tmp
	 ser tmp
	 out DDRB, tmp
	 ldi tmp, (1<<ADLAR|1<<MUX2|1<<MUX1|1<<MUX0)
	 out ADMUX, tmp
	 ldi tmp, (1<<ADEN|1<<ADIE|1<<ADPS0|1<<ADPS1|1<<ADPS2)
	 out ADCSRA, tmp
	 cbi ADCSRA, ADEN
	 ldi r16, LOW(RAMEND)
	 out SPL, r16
	 ldi r16, HIGH(RAMEND)
	 out SPH, r16
main_loop:
	 cpi rmode, 2
	 breq start_adc
	 cpi rmode, 1
	 breq start_print
	 ldi tmp, 0x81
	 out PORTB, tmp
	 rjmp main_loop
start_adc:
	 clr tmp
	 out PORTB, tmp
	 rjmp main_loop
start_print:
	 out PORTB, leds
	 rjmp main_loop
	 
	 
button_int0:
	 ldi rmode, 1
	 ldi YL, LOW(digits)
	 ldi YH, HIGH(digits)
	 ldi r20, digits_size
	 ld leds, Y
	 ldi tmp, (1 << CS02 | 1 << CS00)
	 out TCCR0, tmp
	 reti

button_int1:
	 sbi ADCSRA, ADEN
	 ldi rmode, 2	 
	 ldi YL, LOW(digits)
	 ldi YH, HIGH(digits)
	 ldi r20, digits_size
	 sbi ADCSRA, ADSC
	 reti
	 
	 
timer0_ovf:
	 ld leds, Y
	 adiw YL:YH, 1
	 dec r20
	 brne exit_timer0_precessing
	 ldi rmode, 0
	 clr tmp
	 out PORTB, tmp
	 out TCCR0, tmp
exit_timer0_precessing:
	 reti
	 
adc_int:
	 in r31, ADCH
	 st Y, r31
	 adiw YL:YH, 1
	 sbi ADCSRA, ADSC
	 dec r20
	 brne exit_adcint_precessing
	 cbi ADCSRA, ADEN
	 ldi rmode, 0
exit_adcint_precessing:
	 reti
	
