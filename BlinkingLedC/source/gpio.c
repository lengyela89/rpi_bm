#include <gpio.h>

GPIORegisters_t* GPIO_getRegisters(void) {
    GPIORegisters_t* gpioReg = (GPIORegisters_t*) GPIO_BASE_ADDRESS;

    return gpioReg;
}

void GPIO_setPinFunction(GPIOPin_t pin, GPIOFunction_t function) {
    uint8_t             pos     = pin / 10u;
    uint8_t             shift   = (pin % 10u) * 3u;
    uint32_t            pinFct  = ((function  << shift) | 0xFFFFFFFF);
    GPIORegisters_t*    reg     = GPIO_getRegisters();

    switch (pos) {
        case 0:
            reg->GPFSEL0 &= pinFct;
            break;

        case 1:
            reg->GPFSEL1 &= pinFct;
            break;

        case 2:
            reg->GPFSEL2 &= pinFct;
            break;

        case 3:
            reg->GPFSEL3 &= pinFct;
            break;

        case 4:
            reg->GPFSEL4 &= pinFct;
            break;

        case 5:
            reg->GPFSEL5 &= pinFct;
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
