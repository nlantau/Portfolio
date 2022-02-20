/*
 * branchIfGreaterThan50.asm
 *
 *  Created: 2020-02-22 13:42:02
 *   Author: nlantau
 */

; ***** PROGRAM INSTRUCTIONS *********************************************
; Given instructions:
; a. Write a program such that it:
;		i. Sets the value of register R19 to 55.
;		ii. Checks the content of R19.
;		iii. Displays 8 if the content of R19 > 50 or displays 0 otherwise.
; b. Check the above code by changing the content of R19 to 45.
;
;
; ***** PROGRAM INFORMATION **********************************************
; In main, if subroutine Start is called, the program will compare the value
; 55 with 51 and branch to subroutine displayEight which will display the digit 8
; on the 7-seg LED module.
; 
; If the subroutine controlRoutine is call instead of subroutine Start, the program
; will compare the value 45 with 51 which will cause the subroutine to branch to 
; displayZero
;
; DDRD is an I/O register and sets respective pins to either output (1) or input (0)
; PORTD is an I/O register and sets respective pins to either High (1) or Low (0).
;
; Schematics for the Arduino with breadboard, wires, resistors and 7-seg LED module
; is to be found in Lab 2 report.
;


; ***** INCLUDE FILE AND LISTING *****************************************
.include "m328pdef.inc"
.list

; ***** CPU REGISTER DEFINITIONS *****************************************
.def	valueReg	=		r16
.def	control		=		r17
.def	temp		=		r18

; ***** DATA VALUE DECLARATIONS ******************************************
.equ	value		=		0x37			; 0x37 = 55 in decimal
.equ	controlVal	=		0x2D			; 0x2D = 45 in decimal
.equ	highVal		=		0xFF			; High -> Output for DDRD

; ***** DISPLAY VALUE DECLARATIONS ***************************************
.equ zero			=		0b11111110		; used for displaying nr 0
.equ eight			=		0b11011111		; used for displaying nr 8

; ***** PROGRAM START ****************************************************
.cseg										; Program code starts here
.org 0x0000									; program start at address 0x0000

main:	
	
	call initValueRegisters
	call initDDRD
	call start								; use to display 8
	;call controlRoutine					; use to display 0
	jmp main

; ***** SUBROUTINES ******************************************************
start:
	cpi valueReg, $33						; since brge is branching
	brge displayEight						; if arg1 is > or = to arg2
	brlo displayZero						; we need to compare 55 to 51

controlRoutine:								
	cpi control, $33						; since arg1 < arg2 brge will not occur
	brge displayEight						; but instead brlo will branch
	brlo displayZero

; ***** DISPLAY VALUES ON 7-SEG LED MODULE *******************************
displayZero:
	ldi temp, zero
	out PORTD, temp
	jmp controlRoutine						; this will cause an infinite loop of 
											; controlRoutine and displayZero

displayEight:
	ldi temp, eight
	out PORTD, temp
	jmp start								; this will cause an infinite loop of
											; start and displayEight

; ***** INITIALIZE I/O REGISTERS *****************************************
initValueRegisters:
	ldi valueReg, value						; load valueReg with 55
	ldi control, controlVal					; load control with 45
	ret

initDDRD:									; set DDRD to output
	ldi temp, highVal
	out DDRD, temp
	ret