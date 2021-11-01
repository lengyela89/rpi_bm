.section .init
.globl _start

_start:
	b main

.section .text
main:
	mov sp,#0x8000

	bl prepareBlinking$

	//b simpleBlinking$
	b patternBlinking$


prepareBlinking$:
	push {lr}

	// Set GPIO16 to output mode
	ldr r0, =16
	ldr r1, =1
	bl SetGPIOFunction

	pop {pc}

simpleBlinking$:
	// Switch GPIO16 to OFF
	ldr r0, =16
	ldr r1, =0
	mov r4, r0
	mov r5, r1
	bl SetGPIOPin

	simpleBlinking_loop$:
		ldr r0, =500000
		bl WaitUS

		mov r0, r4
		mov r1, r5

		teq r1,#1
		ldreq r1, =0
		ldreq r5, =0
		bleq SetGPIOPin
		ldrne r1, =1
		ldrne r5, =1
		blne SetGPIOPin

		b simpleBlinking_loop$

patternBlinking$:
	ldr r4, =31

	patternBlinking_loop$:
		ldr r6, =pattern
		ldr r6, [r6]

		lsr r5, r6, r4
		and r5, r5, #1

		ldr r0, =16

		cmp r5, #0
		ldrhi r1, =0
		ldrls r1, =1

		bl SetGPIOPin

		ldr r0, =500000
		bl WaitUS

		cmp r4, #0
		subhi r4, #1
		bhi patternBlinking_loop$

		b patternBlinking$



.section .data
.align 2
pattern:
.int 0b11111111101010100010001000101010

