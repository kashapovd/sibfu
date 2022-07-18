;
; work5.asm
;
; Created: 25.03.2022 12:15:37
; Author: Yaroslav
; Task: op=diff, C_size=16, A_size=B_size=8, 
;		C_start_addr=0x75, item=max, 
;		item_addr=0x8B, sort=desc
;

.dseg
.equ C_size=16
.equ A_size=8
.equ B_size=8
.equ eeprom_addr=0x00
.equ new_c_arr_addr=0x100
.org 0x60
arr_A_mem: .byte A_size
arr_B_mem: .byte B_size
.org 0x75
arr_C_mem: .byte C_size
.org 0x8B
item: .byte 1

.cseg
arr_B_raw: .db 6,2,8,9,15,0,3,5
arr_A_raw: .db 5,1,8,2,1,6,8,3

; load array from program memory to sram
; args: @0 - pointer to the array from program memory
;	@1 - pointer to the array from sram
;	@2 - size of array
.macro LOAD_ARR_TO_MEM
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
	ldi ZL, LOW(2*@0)
	ldi ZH, HIGH(2*@0)
	ldi XL, LOW(@1)
	ldi XH, HIGH(@1)
	ldi rsize, @2
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
.endm

; find max element from array
; args: @0 - pointer to the array
;	@1 - size of array
;	@2 - memory pointer where max element will be placed
.macro MAX_FROM_ARRAY
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
	ldi ZL, LOW(@0)
	ldi ZH, HIGH(@0)
	ldi XL, LOW(@2)
	ldi XH, HIGH(@2)
	ldi rsize, @0
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
.endm

; insertion or selection sort (I don't know :) I just got it from my mind)
; (descending mode). best O(n) avg and worst O(n^2)
; args:	@0 - pointer to th array 
;	@1 - size of array
.macro SORT_ARRAY
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
	ldi ZL, LOW(@0)
	ldi ZH, HIGH(@0)
	ldi ridx, 0
	ldi rsize, @1
element_loop:
	mov rjdx, ridx
	inc rjdx
	cp ridx, rsize
	breq sort_end
	mov YH, ZH
	mov YL, ZL
	ld rkeyi, Z+
	mov XH, ZH
	mov XL, ZL
	ld rkeyj, X
swap_loop:
	cp rjdx, rsize
	breq swap_loop_end
	cp rkeyj, rkeyi
	cpse rkeyj, rkeyi
	brge swap_stage 
	rjmp swap_loop_postroutine
swap_stage:
	swp Y, X
	ld rkeyi, Y
swap_loop_postroutine:
	adiw XH:XL, 1
	ld rkeyj, X
	inc rjdx
	rjmp swap_loop
swap_loop_end:
	inc ridx
	rjmp element_loop
sort_end:
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
.endm

;swap two value in memory space
; args: @0 - memory pointer to var1
;	@1 - memory pointer to var2
.macro swp
	.def rvar1=r22
	.def rvar2=r23
	push rvar1
	push rvar2
	ld rvar1, @0
	ld rvar2, @1
	st @1, rvar1
	st @0, rvar2
	pop rvar2
	pop rvar1
	.undef rvar1
	.undef rvar2
.endm

; make diff with two arrays
; args:	@0 - memory pointer to byte sequence
;	@1 - memory pointer to result array
;	@2 - size of result array
.macro DIFF_ARR
	COPY_ARRAY @0, @1, @2
	SORT_ARRAY @1, @2
	.def ridx=r21
	.def rsize=r22
	.def ritem=r23
	.def rnitem=r24
	push ridx
	push rsize
	push ritem
	push rnitem
	push YL
	push YH
	push XL
	push XH 
	ldi YL, LOW(@1)
	ldi YH, HIGH(@1)
	ldi ridx, @2
uniq_loop:
	ld ritem, Y
	mov XL, YL
	mov XH, YH
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
	push XH 
	push XL
	push YH
	push YL
	push rnitem
	push ritem
	push rsize
	push ridx
	.undef ridx
	.undef rsize
	.undef ritem
	.undef rnitem
.endm

; copy array two array to another place of memory
; args: @0 - pointer to array (source)
; 	@1 - pointer to array (destination)
;	@2 - size of destination array 
.macro COPY_ARRAY
	.def risize=r23
	.def ritem=r22
	push risize
	push ritem
	push ZL
	push ZH
	push XL
	push XH
	ldi ZL, LOW(@0)
	ldi ZH, HIGH(@0)
	ldi XL, LOW(@1)
	ldi XH, HIGH(@1)
	ldi risize, @2
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
.endm

.macro WRITE_ARR_TO_EEPROM
	.def ritem=r22
	.def rsize=r23
	push ritem
	push rsize
	ldi ZL, LOW(@0)
	ldi ZH, HIGH(@0)
	ldi XL, LOW(@2)
	ldi XH, HIGH(@2)
	ldi rsize, @1
write_loop:
	sbic EECR, EEWE
	rjmp write_loop
	out EEARH, XH
	out EEARL, XL
	ld ritem, Z+
	out EEDR, ritem
	sbi EECR, EEMWE
	sbi EECR, EEWE
	adiw XH:XL, 1
	dec rsize
	brne write_loop
	pop ritem
	pop rsize
	.undef ritem
	.undef rsize
.endm

init:
	.def tmp=r16
	ldi r16, LOW(RAMEND)
	out SPL, tmp
	ldi r16, HIGH(RAMEND)
	out SPH, tmp
	ser tmp
	out DDRB, tmp

load_arrays:
	LOAD_ARR_TO_MEM arr_B_raw, arr_B_mem, B_size
	LOAD_ARR_TO_MEM arr_A_raw, arr_A_mem, A_size

diff_arrays:
	DIFF_ARR arr_A_mem, arr_C_mem, C_size

write_array:
	WRITE_ARR_TO_EEPROM arr_C_mem, C_size, eeprom_addr
	nop