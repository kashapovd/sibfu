;
; work1.asm
;
; Created: 05.02.2022 7:38:24
; Author : Yaroslav
; Task: var6 F=2*(A-B)+C, A=68, B=43, C=129, D=149, E=4, G=5
;

.def F=r28
.def A=r31
.def B=r30
.def C=r29
.def D=r27
.def I=r26
.def E=r25
.def R=r20
.equ G=0x05

ldi A,68
ldi B,43
ldi C,129
ldi D,149
ldi E,4

calcF:
	mov F,A
	sub F,B
	add F,F
	add F,C
compDF:
	ldi I,12
	cp D,F
	brlo setI
	rjmp calcE
setI:
	ldi I,9
calcE:
	mul E,I
calcR:
	clr R
	sbrs r0,G
	ser R
end:
	nop
	rjmp end