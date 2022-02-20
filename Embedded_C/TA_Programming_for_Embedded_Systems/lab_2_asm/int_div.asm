/*
 * intDiv.asm
 *
 *  Created: 2020-02-18 12:10:45
 *   Author: nlantau 
 */ 

; ***** PROGRAM INSTRUCTIONS *********************************************
; f. Write a program to perform integer division. 
; Start with the case where the operands are 8-bit integers.

; ***** PROGRAM INFORMATION **********************************************
; Info:
; This program will execute 8-bit integer division. Since there is no
; opcode for division we'll have to use subtraction and a counter, to remember
; the amounts of iterations done in our subtraction-loop.
; Ie. 12/4 = 12-4-4-4, which is 3 iterations ie, the same sum as the quotient 
; from the actual division.
; This division routine works fine while only using the low nibble of 
; each byte.

; ***** INCLUDE FILE AND LISTING *****************************************
.include "m328pdef.inc"
.list

; ***** CPU REGISTER DEFINITIONS *****************************************
.def	numerator		=		r16
.def	denominator		=		r17
.def	quotient		=		r18
.def	counter			=		r5

; ***** DATA VALUE DECLARATIONS ******************************************
.equ	firstValue		=		0x0A
.equ	secondValue		=		0x02

; ***** PROGRAM START ****************************************************
.cseg
.org 0x000

main:
	call initIOreg
	call initXreg
	call clearCounter
	call intDiv
	call exit

; ***** INITIALIZE I/O REGISTERS *****************************************
; Info:
; We start our program by load our desired integers into the registers that
; we'll work with.

initIOreg:
	ldi numerator, firstValue
	ldi denominator, secondValue
	ret

; ***** INITIALIZE X-REGISTER ********************************************
; Info:
; Once the division is completed, we'll store the result to where our x-reg
; is pointing at.
; In this subroutine, we initialize our x-register to point at 0x0100 (SRAM_START)
initXreg:
	ldi xl, $00
	ldi xh, $01
	ret

; ***** CLEAR COUNTER ****************************************************
; Info:
; To make sure that our counter register doesn't contain any data before we 
; start using it as a counter, we clear the counter register ( = 0x00 ).
clearCounter:
	clr counter
	ret

; ***** 1 BYTE DIVISION **************************************************
; Info:
; Again, since we don't have an opcode for division, we'll use subtraction as
; explained in Program Information above.
; For each iteration, out counter will increase by one. This value will be used as
; the result of our division.
; Once the numerator is equal to the denominator, we'll go into subroutine reslut.
intDiv:
	sub numerator, denominator			;numerator = 12-4
	inc counter							;counter++
	cp numerator, denominator			;compare r16 with r17
	brge intDiv							; loop if r16 >= r17
	call result
	ret

; ***** RESULT **********************************************************
; Info:
; Our reslut will be stored at the address where x-reg points at (0x0100)
result:
	st x+, counter
	ret

; ***** INFINITE LOOP ***************************************************
exit:
	jmp exit