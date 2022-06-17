/*
 * AuxiliaryPeripherals.c
 *
 *  Created on: Nov 14, 2021
 *      Author: lengyela
 */

#include <SystemConfiguration.h>
#include <AuxiliaryPeripherals.h>


AUXP_Registers_t* AUXP_getRegisters(void) {
    return ((AUXP_Registers_t*) AUXP_BASE_ADDRESS);
}

bool AUXP_hasPendingInterrupt(AUXP_Peripheral_t peripheral) {
    uint32_t            state       = 0u;
    AUXP_Registers_t*   registers   = AUXP_getRegisters();

    switch (peripheral) {
        case AUXP_PERIPHERALS__MINI_UART:
            state = (registers->AUX_IRQ & AUXP_IRQ__MINI_UART);
            break;

        case AUXP_PERIPHERALS__SPI1:
            state = (registers->AUX_IRQ & AUXP_IRQ__SPI1);
            break;

        case AUXP_PERIPHERALS__SPI2:
            state = (registers->AUX_IRQ & AUXP_IRQ__SPI2);
            break;

        default:
            state = 0u;
    }

    if (0u == state) {
        return false;
    }

    return true;
}

AUXP_PeripheralState_t AUXP_getPeripheralState(AUXP_Peripheral_t peripheral) {
    uint32_t            state       = 0u;
    AUXP_Registers_t*   registers   = AUXP_getRegisters();

    switch (peripheral) {
        case AUXP_PERIPHERALS__MINI_UART:
            state = (registers->AUX_ENABLES & AUXP_ENB__MINI_UART);
            break;

        case AUXP_PERIPHERALS__SPI1:
            state = (registers->AUX_ENABLES & AUXP_ENB__SPI1);
            break;

        case AUXP_PERIPHERALS__SPI2:
            state = (registers->AUX_ENABLES & AUXP_ENB__SPI2);
            break;

        default:
            state = 0u;
    }

    if (0u == state) {
        return AUXP_PERIPHERAL_STATE__DISABLED;
    }

    return AUXP_PERIPHERAL_STATE__ENABLED;
}

void AUXP_setPeripheralState(AUXP_Peripheral_t peripheral, AUXP_PeripheralState_t state) {
    AUXP_Registers_t* registers = AUXP_getRegisters();

    switch (peripheral) {
        case AUXP_PERIPHERALS__MINI_UART:
            registers->AUX_ENABLES |= AUXP_ENB__MINI_UART;
            break;

        case AUXP_PERIPHERALS__SPI1:
            registers->AUX_ENABLES |= AUXP_ENB__SPI1;
            break;

        case AUXP_PERIPHERALS__SPI2:
            registers->AUX_ENABLES |= AUXP_ENB__SPI2;
            break;
    }
}

AUXP_MiniUARTStatusReg_t AUXP_getMiniUARTStatus() {
    AUXP_Registers_t*           registers   = AUXP_getRegisters();

    AUXP_MiniUARTStatusReg_t    result      = {
        .symbolAvailable          = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__SYMBOL_AVAILABLE) >> AUXP_MU_STAT_POS__SYMBOL_AVAILABLE),
        .spaceAvailable           = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__SPACE_AVAILABLE) >> AUXP_MU_STAT_POS__SPACE_AVAILABLE),
        .receiverIdle             = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__RECEIVER_IDLE) >> AUXP_MU_STAT_POS__RECEIVER_IDLE),
        .transmitterIdle          = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__TRANSMITTER_IDLE) >> AUXP_MU_STAT_POS__TRANSMITTER_IDLE),
        .receiverOverrun          = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__RECEIVER_OVERRUN) >> AUXP_MU_STAT_POS__RECEIVER_OVERRUN),
        .transmiFIFOFull          = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__TRANSMIT_FIFO_FULL) >> AUXP_MU_STAT_POS__TRANSMIT_FIFO_FULL),
        .rtsStatus                = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__RTS_STATUS) >> AUXP_MU_STAT_POS__RTS_STATUS),
        .ctsLine                  = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__CTS_LINE) >> AUXP_MU_STAT_POS__CTS_LINE),
        .transmitFIFOEmpty        = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__TRANSMIT_FIFO_EMPTY) >> AUXP_MU_STAT_POS__TRANSMIT_FIFO_EMPTY),
        .transmitterDone          = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__TRANSMITTER_DONE) >> AUXP_MU_STAT_POS__TRANSMITTER_DONE),
        .receiveFIFOFillLevel     = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__RECEIVE_FIFO_FILL_LEVEL) >> AUXP_MU_STAT_POS__RECEIVE_FIFO_FILL_LEVEL),
        .transmitFIFOFillLevel    = ((registers->AUX_MU_STAT_REG & AUXP_MU_STAT__TRANSMIT_FIFO_FILL_LEVEL) >> AUXP_MU_STAT_POS__TRANSMIT_FIFO_FILL_LEVEL)
    };

    return result;
}

uint32_t AUXP_setMiniUARTBaudrate(uint16_t requestedBaudrate) {
    AUXP_Registers_t* registers = AUXP_getRegisters();

    // Calculate baudrate counter value
    uint32_t baudrateCntr = ((SYSC_SYS_CLK_FREQ / (8u * requestedBaudrate)) - 1u) & 0x0000FFFFu;

    // Set baudrate counter value to the appropriate register
    registers->AUX_MU_BAUD_REG = baudrateCntr;

    // Returns the set baudrate
    return (SYSC_SYS_CLK_FREQ / (8u * (baudrateCntr + 1u)));
}
