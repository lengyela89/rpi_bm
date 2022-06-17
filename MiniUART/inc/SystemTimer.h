/*
 * SystemTimer.h
 *
 *  Created on: Nov 4, 2021
 *      Author: lengyela
 */

#ifndef INC_SYSTEMTIMER_H_
#define INC_SYSTEMTIMER_H_

#include <common.h>


#define SYST_BASE_ADDRESS   (0x20003000u)

#define SYST_MATCH_STATUS__CH_0     (1u)
#define SYST_MATCH_STATUS__CH_1     (2u)
#define SYST_MATCH_STATUS__CH_2     (4u)
#define SYST_MATCH_STATUS__CH_3     (8u)
#define SYST_MATCH_STATUS__CH_ALL   (       \
    SYST_MATCH_STATUS__CH_0 |               \
    SYST_MATCH_STATUS__CH_1 |               \
    SYST_MATCH_STATUS__CH_2 |               \
    SYST_MATCH_STATUS__CH_3                 \
)


typedef struct {
    uint32_t    CS;
    uint32_t    CLO;
    uint32_t    CHI;
    uint32_t    C0;
    uint32_t    C1;
    uint32_t    C2;
    uint32_t    C3;
} SYST_Registers_t;

typedef enum {
    SYST_CHANNEL__0    = 0x0u,
    SYST_CHANNEL__1    = 0x1u,
    SYST_CHANNEL__2    = 0x2u,
    SYST_CHANNEL__3    = 0x3u,
    SYST_CHANNEL__ALL  = 0xFFu
} SYST_Channel_t;



SYST_Registers_t* SYST_getRegisters(void);

bool SYST_getChannelMatchStatus(SYST_Channel_t channel);

void SYST_clearChannelMatchStatus(SYST_Channel_t channel);


#endif /* INC_SYSTEMTIMER_H_ */
