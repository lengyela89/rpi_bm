#include <gpio.h>

GPIORegisters_t* GPIO_getRegisters(void) {
    GPIORegisters_t* gpioReg = (GPIORegisters_t*) GPIO_BASE_ADDRESS;

    return gpioReg;
}

void GPIO_setPinFunction(GPIOPin_t pin, GPIOFunction_t function) {
    uint8_t             pos     = pin / 10u;
    uint8_t             shift   = (pin % 10u) * 3u;
    uint32_t            pinFct  = (function  << shift);
    GPIORegisters_t*    reg     = GPIO_getRegisters();

    switch (pos) {
        case 0:
            reg->GPFSEL0 &= ~(7u << shift);
            reg->GPFSEL0 |= pinFct;
            break;

        case 1:
            reg->GPFSEL1 &= ~(7u << shift);
            reg->GPFSEL1 |= pinFct;
            break;

        case 2:
            reg->GPFSEL2 &= ~(7u << shift);
            reg->GPFSEL2 |= pinFct;
            break;

        case 3:
            reg->GPFSEL3 &= ~(7u << shift);
            reg->GPFSEL3 |= pinFct;
            break;

        case 4:
            reg->GPFSEL4 &= ~(7u << shift);
            reg->GPFSEL4 |= pinFct;
            break;

        case 5:
            reg->GPFSEL5 &= ~(7u << shift);
            reg->GPFSEL5 |= pinFct;
            break;
    }
}

void GPIO_setPin(GPIOPin_t pin) {
    GPIORegisters_t* reg = GPIO_getRegisters();

    if (32 > pin) {
        reg->GPSET0 = (0x1u << (pin % 32u));
    } else {
        reg->GPSET1 = (0x1u << (pin % 32u));
    }
}

void GPIO_clearPin(GPIOPin_t pin) {
    GPIORegisters_t* reg = GPIO_getRegisters();

    if (32 > pin) {
        reg->GPCLR0 = (0x1u << (pin % 32u));
    } else {
        reg->GPCLR1 = (0x1u << (pin % 32u));
    }
}

// TODO move wait to timer module
void GPIO_setPinPullUpDown(GPIOPin_t pin, GPIOPinPullUpDown_t pud) {
    GPIORegisters_t* reg = GPIO_getRegisters();

    // Set PUD register
    reg->GPPUD0 = pud;

    // Wait for 150 cycles
    for (uint8_t waitCntr = 0; waitCntr < 150u; waitCntr++) {
        __asm__("nop;");
    }

    // Set PUD clock for the selected pin
    if (32 > pin) {
        reg->GPUDCLK0 = (0x1u << (pin % 32u));
    } else {
        reg->GPUDCLK1 = (0x1u << (pin % 32u));
    }

    // Wait for 150 cycles
    for (uint8_t waitCntr = 0; waitCntr < 150u; waitCntr++) {
        __asm__("nop;");
    }

    // Clear PUD clock
    if (32 > pin) {
        reg->GPUDCLK0 = 0x00u;
    } else {
        reg->GPUDCLK1 = 0x00u;
    }

    // Clear PUD register
    reg->GPPUD0 = GPIO_PIN_PUD__OFF;

    // Wait for 150 cycles
    for (uint8_t waitCntr = 0; waitCntr < 150u; waitCntr++) {
        __asm__("nop;");
    }
}
