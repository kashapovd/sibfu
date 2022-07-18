;
; work6.asm
;
; Created: 05.02.2022 17:58:37
; Author: Yaroslav
; Task: op=diff, C_size=16, A_size=B_size=8, 
;		C_start_addr=0x75, item=max, 
;		item_addr=0x8B, sort=desc
;

.dseg
	 .equ C_size=16
	 .equ A_size=8
	 .equ B_size=8
	 .org 0x60
	 arr_A_mem: .byte A_size
	 arr_B_mem: .byte B_size
	 .org 0x75
	 arr_C_mem: .byte C_size
	 item: .byte 1

	 .def rmode=r23
	 .def tmp_rmode=r21
	 .def tmp=r22
	 .def leds=r24
	 .def tcnt0_persistent=r25
	 .def chim_vector=r26
.cseg
	 .org 0x00
	 rjmp init
	 .org 0x02
	 rjmp xbutton_int0
	 .org 0x04
	 rjmp ybutton_int1
	 .org OC0addr
	 rjmp timer0_comp
	 .org OVF0addr
	 rjmp timer0_ovf

	 arr_B_raw: .db 6,2,8,9,15,0,3,50
	 arr_A_raw: .db 5,1,81,22,1,63,8,31
; load array from program memory to sram
; args: r16:r17(l:h) - pointer to the array from program memory
;		r18:r19 - pointer to the array from sram
;		r20 - size of array
LOAD_ARR_TO_MEM:
	 .def rsize=r22
	 .def ridx=r23
	 .def ritem=r24
	 push rsize
	 push ridx
	 push ritem
	 push ZL
	 push ZH
	 push XL
	 push XH
	 movw ZL, r16
	 movw XL, r18
	 mov rsize, r20 
	 ldi ritem, 0
	 mov ridx, rsize
load_loop:
	 lpm ritem, Z+
	 st X+, ritem
	 dec ridx
	 brne load_loop
load_arr_to_mem_end:
	 pop XH
	 pop XL
	 pop ZH
	 pop ZL
	 pop ritem
	 pop ridx
	 pop rsize
	 .undef rsize
	 .undef ridx
	 .undef ritem
	 ret

; find max element from array
; args: r16:r17 - pointer to the array
;		r18:r19 - memory pointer where max element will be placed
;		r20		- size of array
MAX_FROM_ARRAY:
	 .def rsize=r22
	 .def rmax=r23
	 .def ridx=r24
	 .def ritem=r25
	 push rsize
	 push rmax
	 push ridx
	 push ritem
	 push ZL
	 push ZH
	 push XL
	 push XH
	 movw ZL, r16
	 movw XL, r18
	 mov rsize, r20
	 mov ridx, rsize 
	 ldi ritem, 0
	 ld rmax, Z
find_loop:
	 ld ritem, Z+
	 cp rmax, ritem
	 brlo set_max
	 rjmp after_max_setting
set_max:
	 mov rmax,ritem
after_max_setting:
	 dec ridx
	 brne find_loop
	 rjmp max_from_array_end
max_from_array_end:
	 st X, rmax
	 pop XH
	 pop XL
	 pop ZH
	 pop ZL
	 pop ritem
	 pop ridx
	 pop rmax
	 pop rsize
	 .undef rsize
	 .undef rmax
	 .undef ridx
	 .undef ritem
	 ret

; insertion or selection sort (I don't know :) I just got it from my mind)
; (descending mode). best O(n) avg and worst O(n^2)
; args:	r18:r19(l:h) - pointer to the array 
;		r120	     - size of array
SORT_ARRAY:
	 .def rkeyj=r22
	 .def rkeyi=r21
	 .def rsize=r23
	 .def ridx=r24
	 .def rjdx=r25
	 push rkeyj
	 push rkeyi
	 push rsize
	 push ridx
	 push rjdx
	 push ZL
	 push ZH
	 push XL
	 push XH
	 push YL
	 push YH
	 movw ZL, r18
	 ldi ridx, 0
	 mov rsize, r20
element_loop:
	 mov rjdx, ridx
	 inc rjdx
	 cp ridx, rsize
	 breq sort_end
	 movw YL, ZL
	 ld rkeyi, Z+
	 movw XL, ZL
	 ld rkeyj, X
swap_loop:
	 cp rjdx, rsize
	 breq swap_loop_end
	 cp rkeyj, rkeyi
	 cpse rkeyj, rkeyi
	 brge swap_stage 
	 rjmp swap_loop_postroutine
swap_stage:
	 push r16
	 push r17
	 push r18
	 push r19
	 push r20
	 movw r16, YL
	 movw r18, XL 
	 rcall swp
	 ld rkeyi, Y
	 pop r20
	 pop r19
	 pop r18
	 pop r17
	 pop r16
swap_loop_postroutine:
	 adiw XH:XL, 1
	 ld rkeyj, X
	 inc rjdx
	 rjmp swap_loop
swap_loop_end:
	 inc ridx
	 rjmp element_loop
sort_end:
	 pop YH
	 pop YL
	 pop XH
	 pop XL
	 pop ZH
	 pop ZL
	 pop rjdx
	 pop ridx
	 pop rsize
	 pop rkeyi
	 pop rkeyj
	 .undef rkeyi
	 .undef rkeyj
	 .undef rsize
	 .undef ridx
	 .undef rjdx	
	 ret

;swap two value in memory space
; args: r16:r17(l:h) - memory pointer to var1
;		r18:r19		 - memory pointer to var2
swp:
	 .def rvar1=r22
	 .def rvar2=r23
	 push rvar1
	 push rvar2
	 push ZL
	 push ZH
	 push XL
	 push XH
	 movw ZL, r16
	 movw XL, r18
	 ld rvar1, Z
	 ld rvar2, X
	 st X, rvar1
	 st Z, rvar2
	 pop XH
	 pop XL
	 pop ZH
	 pop ZL
	 pop rvar2
	 pop rvar1
	 .undef rvar1
	 .undef rvar2
	 ret

; make diff with two arrays
; args:	@0 - memory pointer to byte sequence
;	@1 - memory pointer to result array
;	@2 - size of result array
DIFF_ARR:
	 rcall COPY_ARRAY
	 rcall SORT_ARRAY
	 .def ridx=r21
	 .def rsize=r22
	 .def ritem=r23
	 .def rnitem=r24
	 push ridx
	 push rsize
	 push ritem
	 push rnitem
	 push XL
	 push XH
	 push YL
	 push YH
	 movw YL, r16
	 mov ridx, r18
uniq_loop:
	 ld ritem, Y
	 movw XL, YL
	 dec ridx
find_comp_loop:
	 adiw YH:YL, 1
	 ld rnitem, Y
	 cp ritem, rnitem
	 brne uniq_loop
remove_item:
	 ldi rnitem, 0
	 st X, rnitem
	 st Y, rnitem
	 dec ridx
find_comp_loop_post:
	 cpi ridx, 1
	 brne find_comp_loop
uniq_set_loop_end:
	 pop YH
	 pop YL
	 pop XH
	 pop XL
	 pop rnitem
	 pop ritem
	 pop rsize
	 pop ridx
	 rcall SORT_ARRAY
	 .undef ridx
	 .undef rsize
	 .undef ritem
	 .undef rnitem
	 ret

; copy array two array to another place of memory
; args: @0 - pointer to array (source)
; 	@1 - pointer to array (destination)
;	@2 - size of destination array 
COPY_ARRAY:
	 .def risize=r23
	 .def ritem=r22
	 push risize
	 push ritem
	 push ZL
	 push ZH
	 push XL
	 push XH
	 movw ZL, r16
	 movw XL, r18
	 mov risize, r20
	
copy_loop:
	 ld ritem, Z+
	 st X+, ritem
	 dec risize
	 brne copy_loop
	
copy_array_end:
	 pop XH
	 pop XL
	 pop ZH
	 pop ZL
	 pop ritem
	 pop risize
	 .undef risize
	 .undef ritem
	 ret

init:
	 clr tmp
	 out TCCR0, tmp
	 sei
	 ldi tmp, (1 << ISC01 | 1 << ISC11)
	 out MCUCR, tmp
	 ldi tmp, (1 << INT0 | 1 << INT1)
	 out GICR, tmp
	 ser tmp
	 out DDRB, tmp
	 ldi tmp_rmode, 1 
	 ldi tmp, 0
	 ldi r16, LOW(RAMEND)
	 out SPL, r16
	 ldi r16, HIGH(RAMEND)
	 out SPH, r16

load_arrays:
	 ldi r16, LOW(2*arr_B_raw)
	 ldi r17, HIGH(2*arr_B_raw)
	 ldi r18, LOW(arr_B_mem)
	 ldi r19, HIGH(arr_B_mem)
	 ldi r20, B_size
	 rcall LOAD_ARR_TO_MEM

	 ldi r16, LOW(2*arr_A_raw)
	 ldi r17, HIGH(2*arr_A_raw)
	 ldi r18, LOW(arr_A_mem)
	 ldi r19, HIGH(arr_A_mem)
	 ldi r20, A_size
	 rcall LOAD_ARR_TO_MEM

diff_arrays:
	 ldi r16, LOW(arr_A_mem)
	 ldi r17, HIGH(arr_A_mem)
	 ldi r18, LOW(arr_C_mem)
	 ldi r19, HIGH(arr_C_mem)
	 ldi r20, C_size
	 rcall DIFF_ARR

find_max:
	 ldi r16, LOW(arr_C_mem)
	 ldi r17, HIGH(arr_C_mem)
	 ldi r18, LOW(item)
	 ldi r19, HIGH(item)
	 ldi r20, C_size
	 rcall MAX_FROM_ARRAY
	 nop
	 
main_loop:
	 cpi rmode, 1
	 brsh prepare_leds
	 mov leds, tmp_rmode
prepare_leds:
	 out PORTB, leds
	 rjmp main_loop

xbutton_int0:
	 ldi tmp, 4
	 inc tmp_rmode
	 cpse tmp_rmode, tmp
	 reti
	 ldi tmp_rmode, 1
	 reti

ybutton_int1:
	 cpi rmode, 0
	 breq load_mode
	 ldi rmode, 0
	 reti
load_mode:
	 mov rmode, tmp_rmode
	 cpi rmode, 2
	 breq configure_second_mode
	 cpi rmode, 3
	 breq configure_third_mode
	 cpi rmode, 1
	 breq configure_first_mode
configure_first_mode:
	 ldi tmp, (1<<TOIE0)
	 out TIMSK, tmp
	 ldi tmp, (1 << CS00| 1<<CS02)
	 out TCCR0, tmp
	 ldi r18, LOW(arr_C_mem)
	 ldi r19, HIGH(arr_C_mem)
	 ldi r20, C_size
	 movw YL, r18
	 ld leds, Y
	 reti
configure_second_mode:
	 clr leds
	 ldi tmp, (1<<TOIE0)
	 out TIMSK, tmp
	 ldi tcnt0_persistent, 0xFE
	 out TCNT0, tcnt0_persistent
	 ldi tmp, (1 << CS01 | 1 << CS00)
	 out TCCR0, tmp
	 reti
configure_third_mode:
	 ldi tmp, (1<<OCIE0)
	 out TIMSK, tmp
	 ldi tcnt0_persistent, 100
	 out OCR0, tcnt0_persistent
	 out TCNT0, tcnt0_persistent
	 ldi tmp, (1 << CS01 | 1 << CS00)
	 out TCCR0, tmp
	 reti 
	 
timer0_ovf:
	 cpi rmode, 1
	 breq process_timer0_for_first_mode
	 cpi rmode, 2
	 breq process_timer0_for_second_mode
	 reti
process_timer0_for_second_mode:
         com leds
	 dec tcnt0_persistent
	 cpi tcnt0_persistent, 0
	 breq renew_tcnt0_persistent
	 rjmp prepare_tcnt0
renew_tcnt0_persistent:
	 ser tcnt0_persistent
prepare_tcnt0:
	 out TCNT0, tcnt0_persistent
	 rjmp exit_timer0_precessing 
process_timer0_for_first_mode:
	 ld leds, Y
	 adiw YL:YH, 1
	 dec r20
	 brne exit_timer0_precessing
	 ldi YL, LOW(arr_C_mem)
	 ldi YH, HIGH(arr_C_mem)
	 ldi r20, C_size
exit_timer0_precessing:
	 reti
	 
timer0_comp:
	 ;
	 reti
	