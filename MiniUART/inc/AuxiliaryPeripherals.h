/*
 * AuxiliaryPeripherals.h
 *
 *  Created on: Nov 11, 2021
 *      Author: lengyela
 */

#ifndef INC_AUXILIARYPERIPHERALS_H_
#define INC_AUXILIARYPERIPHERALS_H_

#include <common.h>


#define AUXP_BASE_ADDRESS   (0x20215000u)


/* IRQ register */
#define AUXP_IRQ__MINI_UART     (0x00000001u)
#define AUXP_IRQ__SPI1          (0x00000002u)
#define AUXP_IRQ__SPI2          (0x00000004u)

#define AUXP_IRQ_POS__MINI_UART (0x00000000u)
#define AUXP_IRQ_POS__SPI1      (0x00000001u)
#define AUXP_IRQ_POS__SPI2      (0x00000002u)


/* ENB register */
#define AUXP_ENB__MINI_UART     (0x00000001u)
#define AUXP_ENB__SPI1          (0x00000002u)
#define AUXP_ENB__SPI2          (0x00000004u)

#define AUXP_ENB_POS__MINI_UART (0x00000000u)
#define AUXP_ENB_POS__SPI1      (0x00000001u)
#define AUXP_ENB_POS__SPI2      (0x00000002u)


/* Mini UART status register */
#define AUXP_MU_STAT__SYMBOL_AVAILABLE          (0x00000001u)
#define AUXP_MU_STAT__SPACE_AVAILABLE           (0x00000002u)
#define AUXP_MU_STAT__RECEIVER_IDLE             (0x00000004u)
#define AUXP_MU_STAT__TRANSMITTER_IDLE          (0x00000008u)
#define AUXP_MU_STAT__RECEIVER_OVERRUN          (0x00000010u)
#define AUXP_MU_STAT__TRANSMIT_FIFO_FULL        (0x00000020u)
#define AUXP_MU_STAT__RTS_STATUS                (0x00000040u)
#define AUXP_MU_STAT__CTS_LINE                  (0x00000080u)
#define AUXP_MU_STAT__TRANSMIT_FIFO_EMPTY       (0x00000100u)
#define AUXP_MU_STAT__TRANSMITTER_DONE          (0x00000200u)
#define AUXP_MU_STAT__RECEIVE_FIFO_FILL_LEVEL   (0x000F0000u)
#define AUXP_MU_STAT__TRANSMIT_FIFO_FILL_LEVEL  (0x00F00000u)

#define AUXP_MU_STAT_POS__SYMBOL_AVAILABLE          (0x00000000u)
#define AUXP_MU_STAT_POS__SPACE_AVAILABLE           (0x00000001u)
#define AUXP_MU_STAT_POS__RECEIVER_IDLE             (0x00000002u)
#define AUXP_MU_STAT_POS__TRANSMITTER_IDLE          (0x00000003u)
#define AUXP_MU_STAT_POS__RECEIVER_OVERRUN          (0x00000004u)
#define AUXP_MU_STAT_POS__TRANSMIT_FIFO_FULL        (0x00000005u)
#define AUXP_MU_STAT_POS__RTS_STATUS                (0x00000006u)
#define AUXP_MU_STAT_POS__CTS_LINE                  (0x00000007u)
#define AUXP_MU_STAT_POS__TRANSMIT_FIFO_EMPTY       (0x00000008u)
#define AUXP_MU_STAT_POS__TRANSMITTER_DONE          (0x00000009u)
#define AUXP_MU_STAT_POS__RECEIVE_FIFO_FILL_LEVEL   (0x00000010u)
#define AUXP_MU_STAT_POS__TRANSMIT_FIFO_FILL_LEVEL  (0x00000018u)


typedef struct {
    uint32_t    AUX_IRQ;                            // 0x....5000 Auxiliary Interrupt status
    uint32_t    AUX_ENABLES;                        // 0x....5004 Auxiliary enables
    uint8_t     _RES1[56];                          // 0x....5008 RESERVED
    uint32_t    AUX_MU_IO_REG;                      // 0x....5040 Mini Uart I/O Data
    uint32_t    AUX_MU_IER_REG;                     // 0x....5044 Mini Uart Interrupt Enable
    uint32_t    AUX_MU_IIR_REG;                     // 0x....5048 Mini Uart Interrupt Identify
    uint32_t    AUX_MU_LCR_REG;                     // 0x....504C Mini Uart Line Control
    uint32_t    AUX_MU_MCR_REG;                     // 0x....5050 Mini Uart Modem Control
    uint32_t    AUX_MU_LSR_REG;                     // 0x....5054 Mini Uart Line Status
    uint32_t    AUX_MU_MSR_REG;                     // 0x....5058 Mini Uart Modem Status
    uint32_t    AUX_MU_SCRATCH;                     // 0x....505C Mini Uart Scratch
    uint32_t    AUX_MU_CNTL_REG;                    // 0x....5060 Mini Uart Extra Control
    uint32_t    AUX_MU_STAT_REG;                    // 0x....5064 Mini Uart Extra Status
    uint32_t    AUX_MU_BAUD_REG;                    // 0x....5068 Mini Uart Baudrate
    uint8_t     _RES2[20];                          // 0x....506C RESERVED
    uint32_t    AUX_SPI0_CNTL0_REG;                 // 0x....5080 SPI 1 Control register 0
    uint32_t    AUX_SPI0_CNTL1_REG;                 // 0x....5084 SPI 1 Control register 1
    uint32_t    AUX_SPI0_STAT_REG;                  // 0x....5088 SPI 1 Status
    uint8_t     _RES3[4];                           // 0x....508C RESERVED
    uint32_t    AUX_SPI0_IO_REG;                    // 0x....5090 SPI 1 Data
    uint32_t    AUX_SPI0_PEEK_REG;                  // 0x....5094 SPI 1 Peek
    uint8_t     _RES4[40];                          // 0x....5098 RESERVED
    uint32_t    AUX_SPI1_CNTL0_REG;                 // 0x....50C0 SPI 2 Control register 0
    uint32_t    AUX_SPI1_CNTL1_REG;                 // 0x....50C4 SPI 2 Control register 1
    uint32_t    AUX_SPI1_STAT_REG;                  // 0x....50C8 SPI 2 Status
    uint32_t    AUX_SPI1_IO_REG;                    // 0x....50D0 SPI 2 Data
    uint32_t    AUX_SPI1_PEEK_REG;                  // 0x....50D4 SPI 2 Peek
} AUXP_Registers_t;

typedef enum {
    AUXP_PERIPHERALS__MINI_UART = 0x0u,
    AUXP_PERIPHERALS__SPI1      = 0x1u,
    AUXP_PERIPHERALS__SPI2      = 0x2u
} AUXP_Peripheral_t;

typedef enum {
    AUXP_PERIPHERAL_STATE__DISABLED = 0x0u,
    AUXP_PERIPHERAL_STATE__ENABLED  = 0x1u
} AUXP_PeripheralState_t;

// TODO is it needed here?
typedef struct {
    uint32_t    symbolAvailable         : 1;
    uint32_t    spaceAvailable          : 1;
    uint32_t    receiverIdle            : 1;
    uint32_t    transmitterIdle         : 1;
    uint32_t    receiverOverrun         : 1;
    uint32_t    transmiFIFOFull         : 1;
    uint32_t    rtsStatus               : 1;
    uint32_t    ctsLine                 : 1;
    uint32_t    transmitFIFOEmpty       : 1;
    uint32_t    transmitterDone         : 1;
    uint32_t                            : 6;
    uint32_t    receiveFIFOFillLevel    : 4;
    uint32_t                            : 4;
    uint32_t    transmitFIFOFillLevel   : 4;
    uint32_t                            : 4;
} AUXP_MiniUARTStatusReg_t;



AUXP_Registers_t* AUXP_getRegisters(void);

bool AUXP_hasPendingInterrupt(AUXP_Peripheral_t peripheral);

AUXP_PeripheralState_t AUXP_getPeripheralState(AUXP_Peripheral_t peripheral);

void AUXP_setPeripheralState(AUXP_Peripheral_t peripheral, AUXP_PeripheralState_t state);

AUXP_MiniUARTStatusReg_t AUXP_getMiniUARTStatus();

uint32_t AUXP_setMiniUARTBaudrate(uint16_t requestedBaudrate);



#endif /* INC_AUXILIARYPERIPHERALS_H_ */
