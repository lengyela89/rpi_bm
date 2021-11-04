/*
 * SystemTimer.c
 *
 *  Created on: Nov 4, 2021
 *      Author: lengyela
 */


#include <SystemTimer.h>

SYST_Registers_t* SYST_getRegisters(void) {
    SYST_Registers_t* systReg = (SYST_Registers_t*) SYST_BASE_ADDRESS;

    return systReg;
}

bool SYST_getChannelMatchStatus(SYST_Channel_t channel) {
    SYST_Registers_t* systReg = SYST_getRegisters();

    switch (channel) {
        case SYST_CHANNEL__0:
            return (systReg->CS & SYST_MATCH_STATUS__CH_0);

        case SYST_CHANNEL__1:
            return (systReg->CS & SYST_MATCH_STATUS__CH_1);

        case SYST_CHANNEL__2:
            return (systReg->CS & SYST_MATCH_STATUS__CH_2);

        case SYST_CHANNEL__3:
            return (systReg->CS & SYST_MATCH_STATUS__CH_3);

        default:
            return 0u;
    }
}

void SYST_clearChannelMatchStatus(SYST_Channel_t channel) {
    SYST_Registers_t* systReg = SYST_getRegisters();

    switch (channel) {
        case SYST_CHANNEL__0:
            systReg->CS ^= SYST_MATCH_STATUS__CH_0;
            break;

        case SYST_CHANNEL__1:
            systReg->CS ^= SYST_MATCH_STATUS__CH_1;
            break;

        case SYST_CHANNEL__2:
            systReg->CS ^= SYST_MATCH_STATUS__CH_2;
            break;

        case SYST_CHANNEL__3:
            systReg->CS ^= SYST_MATCH_STATUS__CH_3;
            break;

        case SYST_CHANNEL__ALL:
            systReg->CS ^= SYST_MATCH_STATUS__CH_ALL;
    }
}
