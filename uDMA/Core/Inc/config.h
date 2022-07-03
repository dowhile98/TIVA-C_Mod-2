/*
 * config.h
 *
 *  Created on: 5 mar. 2022
 *      Author: Lenovo
 */

#ifndef CORE_INC_CONFIG_H_
#define CORE_INC_CONFIG_H_

/*******************************************************************/
#include <stdint.h>
#include <inc/hw_gpio.h>
#include <inc/tm4c123gh6pm.h>
/******************************************************************/
#define LED_R           F , 1
#define LED_G           F , 3
#define LED_B           F , 2
#define SW1             F , 0
#define SW2             F , 4

/******************************************************************/
#define BITBAND_ACCESS(a, b)  (*(volatile uint32_t*)(((uint32_t)a & 0xF0000000) + 0x2000000 + (((uint32_t)a & 0x000FFFFF) << 5) + (b << 2)))

#define GPIOA_BASE              0x40004000
#define GPIOB_BASE              0x40005000
#define GPIOC_BASE              0x40006000
#define GPIOD_BASE              0x40007000
#define GPIOE_BASE              0x40024000
#define GPIOF_BASE              0x40025000


#define ENABLE                  1
#define DISABLE                 0
#define DIR_INPUT               0
#define DIR_OUTPUT              1
#define DEN_DIG_DISABLE         0
#define DEN_DIG_ENABLE          1
#define PUR_ENABLE              1
#define PUR_DISABLE             0
#define PDR_DISABLE             0
#define PDR_ENABLE              1
/*****************************************************************/
#define GPIOX_AFSEL_(a, b, c)  BITBAND_ACCESS((GPIO ## b ## _BASE) + GPIO_O_AFSEL, c) = a
#define GPIOX_AFSEL(a, b)      GPIOX_AFSEL_(a, b)

#define GPIOX_DIR_(a, b, c)     BITBAND_ACCESS((GPIO ## b ## _BASE) + GPIO_O_DIR, c) = a
#define GPIOX_DIR(a, b)         GPIOX_DIR_(a, b)

#define GPIOX_DEN_(a, b, c)     BITBAND_ACCESS((GPIO ## b ## _BASE) + GPIO_O_DEN, c) = a
#define GPIOX_DEN(a, b)         GPIOX_DEN_(a, b)

#define GPIOX_PUR_(a, b, c)     BITBAND_ACCESS((GPIO ## b ## _BASE) + GPIO_O_PUR, c) = a
#define GPIOX_PUR(a, b)         GPIOX_PUR_(a, b)

#define GPIOX_PDR_(a, b, c)     BITBAND_ACCESS((GPIO ## b ## _BASE) + GPIO_O_PDR, c) = a
#define GPIOX_PDR(a, b)         GPIOX_PDR_(a, b)

#define GPIOX_PCTL_(a, b, c)    GPIO_PORT ## b ## _PCTL_R = (GPIO_PORT ## b ## _PCTL_R & ~(0x0F << (4 * (c & 7)))) | (a << (4 * (c & 7)))
#define GPIOX_PCTL(a, b)        GPIOX_PCTL_(a, b)

#define GPIOX_DATA_(a, b)       BITBAND_ACCESS((GPIO ## a ## _BASE) + 0x3FC, b)
#define GPIOX_DATA(a)           GPIOX_DATA_(a)

#define GPIOX_ODR_(a, b, c)     BITBAND_ACCESS((GPIO ## b ## _BASE) + GPIO_O_ODR, c) = a
#define GPIOX_ODR(a)            GPIOX_ODR_(a)

#define GPIOX_PIN_(a, b)        b
#define GPIOX_PIN(a)            GPIOX_PIN_(a)

#define GPIOX_PORT_(a, b)       GPIO ## a
#define GPIOX_PORT(a)           GPIOX_PORT_(a)

#define GPIOX_CLOCK_(a, b)      SYSCTL_RCGC2_GPIO ## a
#define GPIOX_CLOCK(a)          GPIOX_CLOCK_(a)

#define GPIOX_EN_CLOCK_(a, b)   {SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIO ## a;\
                                 while(!(SYSCTL_PRGPIO_R & SYSCTL_RCGC2_GPIO ## a));}
#define GPIOX_EN_CLOCK(a)       GPIOX_EN_CLOCK_(a)


#define GPIOX_UNLOCK_(a, b)     {GPIO_PORT ## b ## _LOCK_R = 0x4C4F434B; \
                                 GPIO_PORT ## b ## _CR_R |= 1U<< (b);}
#define GPIOX_UNLOCK(a)         GPIOX_UNLOCK_(a)



#endif /* CORE_INC_CONFIG_H_ */
