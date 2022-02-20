/*
 * NC_2byteIntDiv.asm
 *
 *  Created: 2020-02-22 17:39:58
 *   Author: nlantau
 */ 
 
; ***** PROGRAM INSTRUCTIONS *********************************************
; e. Repeat the above for 16-bit subtraction.
; f. Write a program to perform integer division. 
; Start with the case where the operands are 8-bit integers. 
; Use your code in (e) above to perform 16-bit integer division.

; ***** PROGRAM INFORMATION **********************************************
; Info:
; This program will perform 16-bit integer division. It's only been implemented
; with the low nibble set in the low byte of the operands.
; The program uses the same principle as in 8-bit division -> Since there is no
; opcode for division, we'll subtract until the low bytes are equal and by the usage of
; a counter we'll know how many iterations we've done (ei we know the quotient after 
; our division routine is done).
; We store the result at the address where our Y-register points at.
;


; ***** INCLUDE FILE AND LISTING *****************************************
.include "m328pdef.inc"
.list

; ***** CPU REGISTER DEFINITIONS *****************************************
.def	firstLow		=		r16
.def	firstHigh		=		r17
.def	secondLow		=		r18
.def	secondHigh		=		r19
.def	sumLow			=		r20
.def	sumHigh			=		r21
.def	temp			=		r22
.def	counter			=		r5

; ***** DATA VALUE DECLARATIONS ******************************************
; Info:
; Change the values of firstValue and secondValue for different sums.
;
.equ	firstValueLow	=		0x0A		
.equ	firstValueHigh	=		0x00		; 0x00:04		
.equ	secondValueLow	=		0x02
.equ	secondValueHigh	=		0x00		; 0x00:01	= 0x0004
.equ	xRegLow			=		0x00
.equ	xRegHigh		=		0x01		; 0x0100 = x-register points at
.equ	yRegLow			=		0x10		
.equ	yRegHigh		=		0x01		; 0x0110 = y-register points at

; ***** PROGRAM START ****************************************************
.cseg
.org 0x0000	

main:
	call initIOreg
	call initXandYreg
	call storeValueInMemory
	call loadValueFromMemory
	call divisionTwoBytes
	call storeSumInMemory
	call exit

; ***** INITIALIZE I/O REGISTERS *****************************************
; Info:
; First, we start of by storing our desired values into our working registers.
; These values will be stored at the addresses at where X-register point at,
; in subroutine storeValueInMemory
initIOreg:
	ldi firstLow, firstValueLow
	ldi firstHigh, firstValueHigh
	ldi secondLow, secondValueLow
	ldi secondHigh, secondValueHigh
	ret
	
; ***** INITIALIZE X- AND Y-POINTER **************************************
; Info:
; We'll use the addresses where X- and Y-registers points at to store and load our
; numbers that we'll use in our arithmetic operations
initXandYreg:
	ldi xl, xRegLow
	ldi xh, xRegHigh
	ldi yl, yRegLow
	ldi yh, yRegHigh
	ret

; ***** STORE VALUE TO MEMORY ********************************************
; Info:
; As we store our values into SRAM (where we've set X-reg to point at), we
; also have to increment the value of the X-reg to not overwrite data.
; x+ will increment the value of x-reg by one which means that x-reg now points
; at the next address. Then we'll store the next value at that address.
storeValueInMemory:
	st x+, firstLow
	st x+, firstHigh
	st x+, secondLow
	st x+, secondHigh
	ret

; ***** LOAD VALUE FROM MEMORY *******************************************
; Info:
; To load from memory, we use the value which our x-reg points at -> We decrement
; the pointer and then fetch the value that's stored at the newly decremented address.
; Ie. if x-reg points at 0x0101, it first decrements by one to 0x0100 and then fetches
; the data stored at 0x0100.
loadValueFromMemory:
	ld secondHigh, -x
	ld secondLow, -x
	ld firstHigh, -x
	ld firstLow, -x
	ret

; ***** STORE SUM IN MEMORY **********************************************
; Info:
; We move our counter value into our sumLow register.
; Next, we store our sumLow at the address at where our Y-reg points at.
storeSumInMemory:
	mov sumLow, counter
	st y+, sumLow
	ret	
	
; ***** 2 BYTE DIVISION **************************************************
; Info:
; To subtract to 16-bit registers we need to use opcode sub (for the low bytes) and 
; opcode sbc (for the high bytes). Sbc will allow the operation to do a correct
; subtraction if the low byte sub has got a carry.
; We'll do this until our firstLow register = secondLow register. During each iteration
; we'll increase our counter value by one (= our quotient).
divisionTwoBytes:
	sub firstLow, secondLow				 
	sbc firstHigh, secondHigh	
	inc counter
	cp firstLow, secondLow
	brge divisionTwoBytes
	ret
; ***** EXIT PROGRAM *****************************************************
exit:
	.exit