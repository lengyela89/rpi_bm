.globl GetGPIOBaseAddress
.globl SetGPIOFunction
.globl SetGPIOPin
.globl SetGPIOPinON
.globl SetGPIOPinOFF

// Returns GPIO base address in R0
GetGPIOBaseAddress:
	ldr r0,=0x20200000

	// Return to the caller
	mov pc, lr


// r0[in] - GPIO Pin number {0..53}
// r1[in] - GPIO Function {0..7}
SetGPIOFunction:
	// Validate r0; it must be lower or equal to 53
	cmp r0, #53
	movhi pc, lr

	// Validate r1; it must be lower or equal to 7
	cmp r1, #7
	movhi pc, lr

	mov r2, r0
	push {lr}
	bl GetGPIOBaseAddress

	SetGPIOFunction_loop$:
		cmp r2, #9
		subhi r2, #10
		addhi r0, #4
		bhi SetGPIOFunction_loop$

	// Multiply r2 by 3
	add r2, r2,lsl #1
	lsl r1, r2
	str r1, [r0]

	// Return to the caller
	pop {pc}


// r0[in] - GPIO Pin number {0..53}
// r1[in] - GPIO Pin value {0 => OFF, >0 => ON}
SetGPIOPin:
	// Validate r0; it must be lower or equal to 53
	cmp r0, #53
	movhi pc, lr

	push {r4, r5, r6, r7, lr}

	mov r4, r1
	teq	r4, #0
	bleq SetGPIOPinOFF
	teq	r4, #0
	blne SetGPIOPinON

	// Return to the caller
	pop {r4, r5, r6, r7, pc}


// r0[in] - GPIO Pin number {0..53}
SetGPIOPinON:
	// Validate r0; it must be lower or equal to 53
	cmp r0, #53
	movhi pc, lr

	cmp r0, #31
	ldrls r1, =0x2020001C
	ldrhi r1, =0x20200020
	subhi r0, #32

	ldr r2, =1
	lsl r2, r0

	str r2, [r1]

	mov pc, lr


// r0[in] - GPIO Pin number {0..53}
SetGPIOPinOFF:
	// Validate r0; it must be lower or equal to 53
	cmp r0, #53
	movhi pc, lr

	cmp r0, #31
	ldrls r1, =0x20200028
	ldrhi r1, =0x2020002C
	subhi r0, #32

	ldr r2, =1
	lsl r2, r0

	str r2, [r1]

	mov pc, lr
