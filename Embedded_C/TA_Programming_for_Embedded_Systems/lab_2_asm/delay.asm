/*
 * NC_delay.asm
 *
 *  Created: 2020-02-22 18:03:44
 *   Author: nlantau
 */ 

; ***** PROGRAM INSTRUCTIONS *********************************************
; 2.
; One of the important aspects of real-time applications is accurate timing of tasks. 
; Write a code that produces a delay of 1msec.
; Explain how you estimated the duration of the loop.
; Repeat the above for delays of 10ms, 100ms, 1s, 10sec.

; ***** PROGRAM INFORMATION **********************************************
; Info:
; This program demonstrates how different sized delays might look like. Using
; branching, decrementing register values and loops might give the user very accurate
; results in Atmel Studio simulator, during debugging.
; The reality will most likely differ and give longer delays, due to hardware not always
; performing at exactly 16MHz and possibly other factors as well.
;

; ***** INCLUDE FILE AND LISTING *****************************************
.include "m328pdef.inc"
.list

; ***** CPU REGISTER DEFINITIONS *****************************************
.def	firstReg			=		r16
.def	secondReg			=		r17
.def	thirdReg			=		r18
.def	fourthReg			=		r19

; ***** DATA VALUE DECLARATIONS ******************************************
; Info:
; In this section we store the specific values that we want to load into our registers
; to get wanted lenght in our delays.
; These values have been tested in Atmel Studio simulator and will give us very precise
; results. The numbers are taken from an online calculator (http://www.bretmulvey.com/avrdelay.html)
; and applied in this program
.equ	oneMsValOne			=		199
.equ	oneMsValTwo			=		21
;
.equ	tenMsValOne			=		202
.equ	tenMsValTwo			=		208
;
.equ	hundredMsValOne		=		229
.equ	hundredMsValTwo		=		30
.equ	hundredMsValThree	=		9
;
.equ	oneSecValOne		=		0
.equ	oneSecValTwo		=		43
.equ	oneSecValThree		=		82
;
.equ	tenSecValOne		=		21
.equ	tenSecValTwo		=		175
.equ	tenSecValThree		=		44
.equ	tenSecValFour		=		4

; ***** PROGRAM START ****************************************************
.cseg
.org 0x000
main:
	call initIOregOneMs				; load registers with 1ms values
	call delayTwoRegs				; execute 1ms delay
	;
	call initIOregTenMs				; load registers with 10ms values
	call delayTwoRegs				; execute 10ms delay
	;
	call initIOregHundredMs			; load registers with 100ms values
	call delayThreeRegs				; execute 100ms delay
	;
	call initIOregOneSec			; load registers with 1s values
	call delayThreeRegs				; execute 1s delay
	;
	call initIOregTenSec			; load registers with 10s values
	call delayFourRegs				; execute 10s delay
	;
	call exit						; exit program

; ***** INITIALIZE I/O REGISTERS *****************************************
initIOregOneMs:
	ldi firstReg, oneMsValOne
	ldi secondReg, OneMsValTwo
	ret

initIOregTenMs:
	ldi firstReg, tenMsValOne
	ldi secondReg, tenMsValTwo
	ret

initIOregHundredMs:
	ldi firstReg, hundredMsValOne
	ldi secondReg, hundredMsValTwo
	ldi thirdReg, hundredMsValThree
	ret

initIOregOneSec:
	ldi firstReg, oneSecValOne
	ldi secondReg, oneSecValTwo
	ldi thirdReg, oneSecValThree
	ret

initIOregTenSec:
	ldi firstReg, tenSecValOne
	ldi secondReg, tenSecValTwo
	ldi thirdReg, tenSecValThree
	ldi fourthReg, tenSecValFour
	ret

; ***** DELAY SEGMENT ***************************************************
; Info:
; These subroutines will be used to get us the wanted delays.
; For 1ms and 10ms, we use delayTwoRegs.
; For 100ms and 1s, we use delayThreeRegs.
; For 10s delay, we use delayFourRegs.
; The principle is the same for all of the delayXRegs ->
; firstReg will decrement, then brne calls the subroutine it is located within
; until firstReg is of zero value.
; Then secondReg will decrement by one, brne calls the subroutine it is located within
; and firstReg will be decremented -> first brne will call the subroutine it is located
; within.
; The formula will kind of look like this:
; ((firstReg * secondReg * thirdReg + secondReg * thirdReg + thirdReg) * opcode cycles ) / 16*10^6
;
; Important to note is that eventhough it might be correct to the exact cycle in our
; simulator in debugger mode in Atmel Studio, the reality is not the same. We might get one sec
; delay in our simulator, but in reality the same routine might take a bit longer than one sec.
; This is why we might want to use special registers for this assignment instead (timers).
;
delayTwoRegs:
	dec firstReg
	brne delayTwoRegs
	dec secondReg
	brne delayTwoRegs
	ret

delayThreeRegs:
	dec firstReg
	brne delayThreeRegs
	dec secondReg
	brne delayThreeRegs
	dec thirdReg
	brne delayThreeRegs
	ret

delayFourRegs:
	dec firstReg
	brne delayFourRegs
	dec secondReg
	brne delayFourRegs
	dec thirdReg
	brne delayFourRegs
	dec fourthReg
	brne delayFourRegs
	ret
; ***** EXIT ************************************************************
exit:
	.exit