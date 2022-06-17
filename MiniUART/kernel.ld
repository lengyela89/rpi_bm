/******************************************************************************
*	kernel.ld
*	 by Alex Chadwick
*
*	A linker script for generation of raspberry pi kernel images.
******************************************************************************/

SECTIONS {
	/*
	* First and formost we need the .init section, containing the code to 
        * be run first. We allow room for the ATAGs and stack and conform to 
        * the bootloader's expectation by putting this code at 0x8000.
	*/
	.init 0x8000 : {
		__SECT_INIT__BEGIN__:
		*(.init)
		__SECT_INIT__END__:
	}
	
	/* 
	* Next we put the rest of the code.
	*/
	.text : {
		__SECT_TEXT__BEGIN__:
		*(.text)
		__SECT_TEXT__END__:
	}
	
	.rodata : {
        __SECT_RODATA__BEGIN__:
        *(.rodata)
        __SECT_RODATA__END__:
	}
	
	/* 
	* Next we put the data.
	*/
	.data : {
		__SECT_DATA__BEGIN__:
		*(.data)
		__SECT_DATA__END__:
	}

	/*
	* Finally comes everything else. A fun trick here is to put all other 
	* sections into this section, which will be discarded by default.
	*/
	/DISCARD/ : {
		*(*)
	}
}
