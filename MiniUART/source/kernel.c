#include <common.h>
#include <gpio.h>
#include <SystemTimer.h>
#include <AuxiliaryPeripherals.h>


void waitUS(uint32_t time) {
    SYST_Registers_t* systReg = SYST_getRegisters();

    uint32_t timestamp = systReg->CLO;

    while ((systReg->CLO - timestamp) < time) {
        __asm__("nop;");
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

void patternBlinking(uint32_t pattern) {
    for (char i = 0; i < 32u; i++) {
        char status = (pattern >> (31u - i)) & 0x1u;

        waitUS(500000);

        if (1u == status) {
            GPIO_clearPin(GPIO_PIN__16);
        } else {
            GPIO_setPin(GPIO_PIN__16);
        }
    }
}

void configureMiniUART() {
    // TODO set GPIO here

    AUXP_Registers_t* registers = AUXP_getRegisters();

    // Set GPIO14 -> ALT0 (TXD0)
    GPIO_setPinFunction(GPIO_PIN__14, GPIO_FUNC__ALTER5);

    // Set GPIO15 -> ALT0 (RXD0)
    GPIO_setPinFunction(GPIO_PIN__15, GPIO_FUNC__ALTER5);

    // Set GPIO14 (TXD0) to pull-up state
    GPIO_setPinPullUpDown(GPIO_PIN__14, GPIO_PIN_PUD__OFF);

    // Set GPIO15 (RXD0) to pull-up state
    GPIO_setPinPullUpDown(GPIO_PIN__15, GPIO_PIN_PUD__OFF);

    // Enable MiniUART
    AUXP_setPeripheralState(AUXP_PERIPHERALS__MINI_UART, AUXP_PERIPHERAL_STATE__ENABLED);

    // Disable interrupts
    registers->AUX_MU_IER_REG = 0x0u;

    // Disable auto flow control and transmitter/receiver
    registers->AUX_MU_CNTL_REG = 0x0u;

    // Enable 8-bit mode
    registers->AUX_MU_LCR_REG = 0x3u;

    // Set RTS line to be always high
    registers->AUX_MU_MCR_REG = 0x0u;

    AUXP_setMiniUARTBaudrate(115200u);

    // Enable transmit and receive
    registers->AUX_MU_CNTL_REG = 0x3u;
}

void UART_readChar(char* c) {
    if (NULL == c) {
        return;
    }

    AUXP_Registers_t* registers = AUXP_getRegisters();

    *c = '\0';
    uint32_t lsr = registers->AUX_MU_LSR_REG;
    if ((lsr & 0x1) && (lsr & 0x20)) {
        *c = (registers->AUX_MU_IO_REG & 0x000000FF);
    }
}

void UART_sendChar(char c) {
    AUXP_Registers_t* registers = AUXP_getRegisters();

    while(1)
    {
        if(registers->AUX_MU_LSR_REG & 0x20) break;
    }

    registers->AUX_MU_IO_REG = c;
}

void UART_sendString(char* str) {
    if (NULL == str) {
        return;
    }

    uint32_t i = 0u;
    while ('\0' != str[i]) {
        UART_sendChar(str[i]);
        i++;
    }
}

void kernel_main(void) {
    configureMiniUART();

    waitUS(2000000);

    UART_sendString("\r\n");
    UART_sendString("Hello World!\r\n");
    UART_sendString("ECHO mode: ON\r\n");

    char c = 0;
    while (1) {
        UART_readChar(&c);
        if ('\0' != c) {
            UART_sendChar(c);
        }
    }

    simpleBlinking();

    //patternBlinking();
}
