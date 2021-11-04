.section .init

.globl _start
_start:
	// Set stack pointer (sp) to address 0x8000 (maximal stack size is 32KB)
	ldr		sp, =0x8000

	// Call kernel_main function (main entry point)
	b		kernel_main
