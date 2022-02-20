/*
 * NC_addArrayElements.asm
 *
 *  Created: 2020-02-23 13:56:12
 *   Author: nlantau
 */ 
 
; ***** PROGRAM INSTRUCTIONS *********************************************
; 3. Suppose you have an array of integer data (say 10 numbers) in a memory
; a. Write a program to find the largest of these numbers and show the 
; location on the lab deck display
; b. Repeat the above to find the sum of the same numbers.
; ***** PROGRAM INFORMATION **********************************************
; Info:
; This program will add upp all 10 elements of the array and display the 
; sum on the 7-seg LED module.
; The 10 different values will first be stored in data memory (where x-register
; points at). In subroutine addArray we simply load our data from data memory
; and add them together and store the total sum in our "highest" register.
; Once all elements have been added, we send the sum to the 7-seg LED module

; ***** INCLUDE FILE AND LISTING *****************************************
.include "m328pdef.inc"
.list

; ***** CPU REGISTER DEFINITIONS *****************************************
.def	temp		=		r16
.def	highest		=		r17
.def	counter		=		r18
.def	zeroReg		=		r2

; ***** DATA VALUE DECLARATIONS ******************************************
.equ	counterVal	=		0x0A
.equ	highVal		=		0xFF

; ***** DISPLAY VALUE DECLARATIONS ***************************************
.equ zeroDisp		=		0b11111110
.equ oneDisp		=		0b00011000
.equ twoDisp		=		0b11001101
.equ threeDisp		=		0b01011101
.equ fourDisp		=		0b00011011
.equ fiveDisp		=		0b01010111
.equ sixDisp		=		0b11010111
.equ sevenDisp		=		0b00011100
.equ eightDisp		=		0b11011111
.equ nineDisp		=		0b00011111
.equ aDisp			=		0b10111111
.equ bDisp			=		0b11110011
.equ cDisp			=		0b11100110
.equ dDisp			=		0b11111001
.equ eDisp			=		0b11100111
.equ fDisp			=		0b10100111

; ***** ARRAY VALUE DECLARATIONS *****************************************
.equ indexZero		=		0x00
.equ indexOne		=		0x02
.equ indexTwo		=		0x03
.equ indexThree		=		0x04
.equ indexFour		=		0x00
.equ indexFive		=		0x00
.equ indexSix		=		0x00
.equ indexSeven		=		0x00
.equ indexEight		=		0x00
.equ indexNine		=		0x00

; ***** PROGRAM START ****************************************************
.cseg
.org 0x0000

main:
	call initGPreg
	call initXreg
	call initDDRD
	call storeData
	call addArray	
	call compareForDisplay
	

; ***** INITIALIZE GP REGISTERS ******************************************
initGPreg:
	clr temp
	clr zeroReg
	clr highest
	ldi counter, counterVal
	ret

; ***** INITIALIZE X- AND I/O REGISTERS **********************************
initXreg:
	ldi xl, $00
	ldi xh, $01
	ret

initDDRD:									; set DDRD to output
	ldi temp, highVal
	out DDRD, temp
	ret

; ***** MOVE DATA TO MEMORY **********************************************
storeData:
	ldi temp, indexZero
	st x+, temp
	ldi temp, indexOne
	st x+, temp
	ldi temp, indexTwo
	st x+, temp
	ldi temp, indexThree
	st x+, temp
	ldi temp, indexFour
	st x+, temp
	ldi temp, indexFive
	st x+, temp
	ldi temp, indexSix
	st x+, temp
	ldi temp, indexSeven
	st x+, temp
	ldi temp, indexEight
	st x+, temp
	ldi temp, indexNine
	st x+, temp
	ret
; ***** FIND LARGEST VALUE IN ARRAY **************************************
addArray:
	ld temp, -x
	dec counter
	add highest, temp
	cp zeroReg, counter
	brne addArray
	ret

; ***** COMPARE DATA IN MEMORY *******************************************
compareForDisplay:						;if equal -> display routine
	cpi highest, 0
	breq dispZero					
	cpi highest, 1
	breq dispOne
	cpi highest, 2
	breq dispTwo
	cpi highest, 3
	breq dispThree
	cpi highest, 4
	breq dispFour
	cpi highest, 5
	breq dispFive
	cpi highest, 6
	breq dispSix
	cpi highest, 7
	breq dispSeven
	cpi highest, 8
	breq dispEight
	cpi highest, 9
	breq dispNine
	cpi highest, 0x0A
	breq dispA
	cpi highest, 0x0B
	breq dispB
	cpi highest, 0x0C
	breq dispC
	cpi highest, 0x0D
	breq dispD
	cpi highest, 0x0E
	breq dispE
	cpi highest, 0x0F
	breq dispF

; ***** DISPLAY SUM ON 7-SEG LED MODULE **********************************
dispZero:
	ldi temp, zeroDisp
	out PORTD, temp						;high on pins to display 0
	jmp compareForDisplay				
dispOne:
	ldi temp, oneDisp
	out PORTD, temp						;high on pins to display 1
	jmp compareForDisplay
dispTwo:
	ldi temp, twoDisp
	out PORTD, temp						;high on pins to display 2
	jmp compareForDisplay
dispThree:
	ldi temp, threeDisp
	out PORTD, temp						;high on pins to display 3
	jmp compareForDisplay
dispFour:
	ldi temp, fourDisp
	out PORTD, temp						;high on pins to display 4
	jmp compareForDisplay
dispFive:
	ldi temp, fiveDisp
	out PORTD, temp						;high on pins to display 5
	jmp compareForDisplay
dispSix:
	ldi temp, sixDisp
	out PORTD, temp						;high on pins to display 6
	jmp compareForDisplay
dispSeven:
	ldi temp, sevenDisp
	out PORTD, temp						;high on pins to display 7
	jmp compareForDisplay
dispEight:
	ldi temp, eightDisp
	out PORTD, temp						;high on pins to display 8
	jmp compareForDisplay
dispNine:
	ldi temp, nineDisp
	out PORTD, temp						;high on pins to display 9
	jmp compareForDisplay
dispA:
	ldi temp, aDisp
	out PORTD, temp						;high on pins to display A
	jmp compareForDisplay
dispB:
	ldi temp, bDisp
	out PORTD, temp						;high on pins to display B
	jmp compareForDisplay
dispC:
	ldi temp, cDisp
	out PORTD, temp						;high on pins to display C
	jmp compareForDisplay
dispD:
	ldi temp, dDisp
	out PORTD, temp						;high on pins to display D
	jmp compareForDisplay
dispE:
	ldi temp, eDisp
	out PORTD, temp						;high on pins to display E
	jmp compareForDisplay
dispF:
	ldi temp, fDisp
	out PORTD, temp						;high on pins to display F
	jmp compareForDisplay

; ***** EXIT *************************************************************
exit:
	.exit