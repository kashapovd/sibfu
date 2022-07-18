.equ iVal=39998
.equ C_size=16
.equ eeprom_addr=0x00
.dseg
.org 0x75
arr_C_mem: .byte C_size
.org 0x8C
max_item: .byte 1
.org 0x8D
min_item: .byte 1
.cseg

.macro READ_ARR_FROM_EEPROM
	.def ritem=r22
	.def rsize=r23
	push ritem
	push rsize
	ldi ZL, LOW(@1)
	ldi ZH, HIGH(@1)
	ldi XL, LOW(@0)
	ldi XH, HIGH(@0)
	ldi rsize, @2
read_loop:
	sbic EECR, EEWE
	rjmp read_loop
	out EEARH, XH
	out EEARL, XL	
	sbi EECR, EERE
	in ritem, EEDR
	st Z+, ritem
	adiw XH:XL, 1
	dec rsize
	brne read_loop
	pop ritem
	pop rsize
	.undef ritem
	.undef rsize
.endm

.macro FIND_MAX_MIN
	.def ritem=r22
	.def rsize=r23
	push ritem
	push rsize
	ldi ZL, LOW(@0)
	ldi ZH, HIGH(@0)
	ldi rsize, @1
	ldi XL, LOW(@2)
	ldi XH, HIGH(@2)
	ldi YL, LOW(@3)
	ldi YH, HIGH(@3)
place_max:
	ld ritem, Z+
	st X, ritem
find_and_place_min:
	ld ritem, Z+
	cpi ritem, 0
	breq find_loop_end
	st Y, ritem
	dec rsize
	brne find_and_place_min
find_loop_end:
	pop ritem
	pop rsize
	.undef ritem
	.undef rsize
.endm

.macro DELAY
	.def loop_count=r18
	.def iLoopRl=r24
	.def iLoopRh=r25
	push loop_count
	push iLoopRl
	push iLoopRh
	ldi loop_count, @0
delay:
	ldi	iLoopRl,LOW(iVal)
	ldi	iLoopRh,HIGH(iVal)
inner_loop:	
	sbiw iLoopRl,1
	brne inner_loop
	dec	loop_count
	brne delay
	nop

	pop iLoopRh
	pop iLoopRl
	pop loop_count
	.undef loop_count
.endm

.macro PRINT_NUMS
	.def maxn=r22
	.def minn=r23
	push maxn
	push minn
	ldi ZL, LOW(@0)
	ldi ZH, HIGH(@0)
	ldi XL, LOW(@1)
	ldi XH, HIGH(@1)
	ld maxn, Z
	ld minn, X
	com maxn
	com minn
print_loop:
	out PORTB, maxn
	DELAY 10
	out PORTB, minn
	DELAY 10
	rjmp print_loop
	pop minn
	pop maxn
	.undef maxn
	.undef minn
.endm

init:
	.def tmp=r16
	ldi r16, LOW(RAMEND)
	out SPL, tmp
	ldi r16, HIGH(RAMEND)
	out SPH, tmp
	ser tmp
	out DDRB, tmp

read_array:
	READ_ARR_FROM_EEPROM eeprom_addr, arr_C_mem, C_size

find_maxmin:
	FIND_MAX_MIN arr_C_mem, C_size, max_item, min_item

print_maxmin:
	PRINT_NUMS max_item, min_item
	nop
