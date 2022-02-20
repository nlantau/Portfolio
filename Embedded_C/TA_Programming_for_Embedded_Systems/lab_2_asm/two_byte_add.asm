/*
 * _2byteIntAdd.asm
 *
 *  Created: 2020-02-21 22:19:07
 *   Author: nlantau
 */ 

; ***** PROGRAM INSTRUCTIONS *********************************************
; d. Modify your program to add two 16-bit integers from memory and store the result 
; back to memory.

; ***** PROGRAM INFORMATION **********************************************
; Info:
; Given instructions makes the program a bit too complicated -> Since we need to add
; two 16-bit integers from memory, we first need to store those integers into memory.
; Once those are stored into memory (at the address where X-register points at (0x0100),
; we then load our working registers with the data stored where the X-reg points at.
; Once the 16-bit addition is completed, we store the sum at the addresses our
; y-reg points at.


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

; ***** DATA VALUE DECLARATIONS ******************************************
; Info:
; Change the values of firstValue and secondValue for different sums.
;
.equ	firstValueLow	=		0x04		
.equ	firstValueHigh	=		0x02		; 0x02:04		
.equ	secondValueLow	=		0x01
.equ	secondValueHigh	=		0x01		; 0x01:01	= 0x0305
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
	call additionTwoBytes
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
; The movw operation moves an entire word (16-bits) from one 16-bit register
; to another. We'll use this to move our 16-bit sum (which initially is located at
; firstHigh:firstLow) to sumHigh:sumLow.
; Next, we store our sumLow and sumHigh at the address at where our Y-reg points at.
storeSumInMemory:
	movw sumHigh:sumLow, firstHigh:firstLow
	st y+, sumLow
	st y+, sumHigh
	ret	
	
; ***** 2 BYTE ADDITION **************************************************
; Info:
; To add to 16-bit registers we need to use opcode add (for the low bytes) and 
; opcode adc (for the high bytes). Adc will allow the operation to do a correct
; addition if the low byte add has got a carry.
; The 16-bit sum is stored in firstHigh:firstLow
additionTwoBytes:
	add firstLow, secondLow				 
	adc firstHigh, secondHigh			
	ret
; ***** EXIT PROGRAM *****************************************************
exit:
	.exit