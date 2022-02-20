/*
 * multiplyTwoIntegersAndDisplay.asm
 *
 *  Created: 2020-02-22 14:41:53
 *   Author: nlantau
 */ 

; ***** PROGRAM INSTRUCTIONS *********************************************
; c. Write a short program to multiply two integers and display the result. 
; You shall write the integers in two registers in the code itself (no keyboard input). 
; You then show the result on the Lab deck seven segment display. 
; Make sure that the sum is less than 9 so that you can see a correct value on the display.
;
; ***** PROGRAM INFORMATION **********************************************
; Two 8-bit registers will multiply and the product will end up in
; a 16-bit register (2 * 8-bit registers, r1:r0).
; We are only interested in small numbers for this exercise, so we'll only 
; uses the low byte of our result.
; First we initialize our operands with our desired values, initialized our
; DDRD I/O registers as output. The we do the arithmetic, store the low byte as 
; our sum and send it to a comparisment subroutine.
; Once the sum = the compared number, according subroutin will be called 
; to display our sum on the 7-seg LED module.;
;


; ***** INCLUDE FILE AND LISTING *****************************************
.include "m328pdef.inc"
.list	

; ***** CPU REGISTER DEFINITIONS *****************************************
.def	firstInt	=		r16
.def	secondInt	=		r17
.def	temp		=		r18
.def	sumHigh		=		r1
.def	sumLow		=		r0

; ***** DATA VALUE DECLARATIONS ******************************************
; Info:
; Change the values of firstValue and secondValue for different sums.
;
.equ	firstValue	=		0x04			; 0x02 = 2 in decimal
.equ	secondValue	=		0x02			; 0x04 = 4 in decimal
.equ	highVal		=		0xFF			; used to set DDRD to output

; ***** DISPLAY VALUE DECLARATIONS ***************************************
.equ zero			=		0b11011110
.equ one			=		0b00011000
.equ two			=		0b11001101
.equ three			=		0b01011101
.equ four			=		0b00011011
.equ five			=		0b01010111
.equ six			=		0b11010111
.equ seven			=		0b00011100
.equ eight			=		0b11011111
.equ nine			=		0b00011111

; ***** PROGRAM START ****************************************************
; Info:
; This is our program. First we initialize used registers and set DDRD to output.
; Then we execute the operation (multiplication).
; Then we compare our sum to 0-9 and display the matching number on our
; 7-seg LED module.
;
.cseg
.org 0x0000

main:
	call initValueRegisters
	call initDDRD
	call multiplication
	call compare

; ***** MULTIPLY REGISTERS ***********************************************
; Info:
; The sum of firstInt * secondInt will be stored in r1:r0 (high:low).
; r0 = sumLow. Since r0 can't be used in opcode cpi, we need to store 
; the sum in our temp register.
;

multiplication:
	mul firstInt, secondInt
	mov temp, sumLow
	ret
	
; ***** COMPARE SUM WITH INTEGER AND CALL DISPLAY ROUTINE ****************
; Info:
; temp contains the value of sumLow. temp will be compared to each number between
; 0-9, and when the value of temp and the compared number are equal, the according
; subroutine will be called
;
compare:
	cpi temp, 0
	breq dispZero					
	cpi temp, 1
	breq dispOne
	cpi temp, 2
	breq dispTwo
	cpi temp, 3
	breq dispThree
	cpi temp, 4
	breq dispFour
	cpi temp, 5
	breq dispFive
	cpi temp, 6
	breq dispSix
	cpi temp, 7
	breq dispSeven
	cpi temp, 8
	breq dispEight
	cpi temp, 9
	breq dispNine


; ***** INITIALIZE I/O REGISTERS *****************************************
; Info:
; operand registers will be loaded with desired values and DDRD will
; be set to output
;
initValueRegisters:	
	ldi firstInt, firstValue
	ldi secondInt, secondValue
	ret

initDDRD:									; set DDRD to output
	ldi temp, highVal
	out DDRD, temp
	ret

; ***** DISPLAY SUM ON 7-SEG LED MODULE **********************************
; Info:
; Bit-seguence for displaying a specific number will be loaded into temp register
; then the value that temp register holds will be loaded into PORTD which will lead
; to that the 7-seg LED module will display the result of the multiplication
;
dispZero:
	ldi temp, zero
	out PORTD, temp					;high on pins to display 0
	jmp multiplication				
dispOne:
	ldi temp, one
	out PORTD, temp					;high on pins to display 1
	jmp multiplication
dispTwo:
	ldi temp, two
	out PORTD, temp					;high on pins to display 2
	jmp multiplication
dispThree:
	ldi temp, three
	out PORTD, temp					;high on pins to display 3
	jmp multiplication
dispFour:
	ldi temp, four
	out PORTD, temp					;high on pins to display 4
	jmp multiplication
dispFive:
	ldi temp, five
	out PORTD, temp					;high on pins to display 5
	jmp multiplication
dispSix:
	ldi temp, six
	out PORTD, temp					;high on pins to display 6
	jmp multiplication
dispSeven:
	ldi temp, seven
	out PORTD, temp					;high on pins to display 7
	jmp multiplication
dispEight:
	ldi temp, eight
	out PORTD, temp					;high on pins to display 8
	jmp multiplication
dispNine:
	ldi temp, nine
	out PORTD, temp					;high on pins to display 9
	jmp multiplication