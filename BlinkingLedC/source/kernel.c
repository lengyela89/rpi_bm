#include <common.h>
#include <gpio.h>
#include <SystemTimer.h>

void waitUS(uint32_t time) {
    SYST_Registers_t* systReg = SYST_getRegisters();

    uint32_t timestamp = systReg->CLO;

    while ((systReg->CLO - timestamp) < time) {
        ;
    }
}

void simpleBlinking() {
    GPIO_setPinFunction(GPIO_PIN__16, GPIO_FUNC__OUTPUT);

    GPIO_clearPin(GPIO_PIN__16);

    uint8_t status = 1u;
    while (1) {
        waitUS(500000);

        if (1u == status) {
            GPIO_setPin(GPIO_PIN__16);
            status = 0u;
        } else {
            GPIO_clearPin(GPIO_PIN__16);
            status = 1u;
        }
    }
}

void patternBlinking() {
    uint32_t pattern = 0b11111111101010100010001000101010;

    for (char i = 0; i < 32u; i++) {
        char status = (pattern >> (31u - i)) & 0x1u;

        waitUS(500000);

        if (1u == status) {
            GPIO_clearPin(GPIO_PIN__16);
        } else {
            GPIO_setPin(GPIO_PIN__16);
        }

        if (i == 31u) {
            i = -1;
        }
    }
}

void kernel_main(void) {
    // simpleBlinking();

    patternBlinking();
}
