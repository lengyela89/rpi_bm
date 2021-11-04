/*
 * gpio.h
 *
 *  Created on: Nov 1, 2021
 *      Author: lengyela
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_


#include <common.h>


#define GPIO_BASE_ADDRESS   (0x20200000u)

typedef enum GPIO_PIN {
    GPIO_PIN__0     = 0u,
    GPIO_PIN__1     = 1u,
    GPIO_PIN__2     = 2u,
    GPIO_PIN__3     = 3u,
    GPIO_PIN__4     = 4u,
    GPIO_PIN__5     = 5u,
    GPIO_PIN__6     = 6u,
    GPIO_PIN__7     = 7u,
    GPIO_PIN__8     = 8u,
    GPIO_PIN__9     = 9u,
    GPIO_PIN__10    = 10u,
    GPIO_PIN__11    = 11u,
    GPIO_PIN__12    = 12u,
    GPIO_PIN__13    = 13u,
    GPIO_PIN__14    = 14u,
    GPIO_PIN__15    = 15u,
    GPIO_PIN__16    = 16u,
    GPIO_PIN__17    = 17u,
    GPIO_PIN__18    = 18u,
    GPIO_PIN__19    = 19u,
    GPIO_PIN__20    = 20u,
    GPIO_PIN__21    = 21u,
    GPIO_PIN__22    = 22u,
    GPIO_PIN__23    = 23u,
    GPIO_PIN__24    = 24u,
    GPIO_PIN__25    = 25u,
    GPIO_PIN__26    = 26u,
    GPIO_PIN__27    = 27u,
    GPIO_PIN__28    = 28u,
    GPIO_PIN__29    = 29u,
    GPIO_PIN__30    = 30u,
    GPIO_PIN__31    = 31u,
    GPIO_PIN__32    = 32u,
    GPIO_PIN__33    = 33u,
    GPIO_PIN__34    = 34u,
    GPIO_PIN__35    = 35u,
    GPIO_PIN__36    = 36u,
    GPIO_PIN__37    = 37u,
    GPIO_PIN__38    = 38u,
    GPIO_PIN__39    = 39u,
    GPIO_PIN__40    = 40u,
    GPIO_PIN__41    = 41u,
    GPIO_PIN__42    = 42u,
    GPIO_PIN__43    = 43u,
    GPIO_PIN__44    = 44u,
    GPIO_PIN__45    = 45u,
    GPIO_PIN__46    = 46u,
    GPIO_PIN__47    = 47u,
    GPIO_PIN__48    = 48u,
    GPIO_PIN__49    = 49u,
    GPIO_PIN__50    = 50u,
    GPIO_PIN__51    = 51u,
    GPIO_PIN__52    = 52u,
    GPIO_PIN__53    = 53u
} GPIOPin_t;

typedef struct {
    uint32_t GPFSEL0;
    uint32_t GPFSEL1;
    uint32_t GPFSEL2;
    uint32_t GPFSEL3;
    uint32_t GPFSEL4;
    uint32_t GPFSEL5;
    uint32_t _RES0;
    uint32_t GPSET0;
    uint32_t GPSET1;
    uint32_t _RES1;
    uint32_t GPCLR0;
    uint32_t GPCLR1;
    uint32_t _RES2;
    uint32_t GPLEV0;
    uint32_t GPLEV1;
    uint32_t _RES3;
    uint32_t _RES4;
    uint32_t GPEDS0;
    uint32_t GPEDS1;
    uint32_t _RES5;
    uint32_t GPREN0;
    uint32_t GPREN1;
    uint32_t _RES6;
    uint32_t GPFEN0;
    uint32_t GPFEN1;
    uint32_t _RES7;
    uint32_t GPHEN0;
    uint32_t GPHEN1;
    uint32_t _RES8;
    uint32_t GPLEN0;
    uint32_t GPLEN1;
    uint32_t _RES9;
    uint32_t GPAREN0;
    uint32_t GPAREN1;
    uint32_t _RES10;
    uint32_t GPAFEN0;
    uint32_t GPAFEN1;
    uint32_t _RES11;
    uint32_t GPPUD0;
    uint32_t GPUDCLK0;
    uint32_t GPUDCLK1;
    uint8_t _RES12[16];
    uint32_t _TEST;
} GPIORegisters_t;

typedef enum {
    GPIO_FUNC__INPUT    = 0b000,
    GPIO_FUNC__OUTPUT   = 0b001,
    GPIO_FUNC__ALTER0   = 0b100,
    GPIO_FUNC__ALTER1   = 0b101,
    GPIO_FUNC__ALTER2   = 0b110,
    GPIO_FUNC__ALTER3   = 0b111,
    GPIO_FUNC__ALTER4   = 0b011,
    GPIO_FUNC__ALTER5   = 0b010
} GPIOFunction_t;



GPIORegisters_t* GPIO_getRegisters(void);

void GPIO_setPinFunction(GPIOPin_t pin, GPIOFunction_t function);

void GPIO_setPin(GPIOPin_t pin);

void GPIO_clearPin(GPIOPin_t pin);

#endif /* INC_GPIO_H_ */
