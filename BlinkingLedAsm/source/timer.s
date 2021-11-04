.globl GetSystemTimerBaseAddress
.globl GetSystemTimerCounter
.globl WaitUS


// Returns the timer's base address in r0 register
GetSystemTimerBaseAddress:
	ldr r0, =0x20003000

	mov pc, lr

GetSystemTimerCounter:
	push {r4, r5, r6, r7, lr}

	// Loads timer's base address to r0
	bl GetSystemTimerBaseAddress

	mov r4, r0

	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]

	pop {r4, r5, r6, r7, pc}

WaitUS:
	push {r4, r5, r6, r7, lr}

	mov r4, r0

	bl GetSystemTimerCounter
	mov r5, r0
	WaitMS_loop$:
		bl GetSystemTimerCounter
		sub r0, r5
		cmp r0, r4
		blo WaitMS_loop$

	pop {r4, r5, r6, r7, pc}
