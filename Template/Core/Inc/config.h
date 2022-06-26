/*
 * config.h
 *
 *  Created on: 5 mar. 2022
 *      Author: Lenovo
 */

#ifndef CORE_INC_CONFIG_H_
#define CORE_INC_CONFIG_H_

/*******************************************************************/
#include <inc/hw_gpio.h>
#include <inc/tm4c123gh6pm.h>
/******************************************************************/
#define LED_R           F , 1
#define LED_G           F , 2
#define LED_B           F , 3
#define SW1             F , 0
#define SW2             F , 4
/*******************************************************************/

#define BITBAND_SRAM_REF        0x20000000
#define BITBAND_SRAM_BASE       0x22000000
#define BITBAND_SRAM(a,b)       *(volatile uint32_t*)((BITBAND_SRAM_BASE + (a-BITBAND_SRAM_REF)*32 + (b*4))) // Convert SRAM address
#define BITBAND_PERI_REF        0x40000000
#define BITBAND_PERI_BASE       0x42000000
#define BITBAND_PERI(a,b)       *(volatile uint32_t*)((BITBAND_PERI_BASE + ((uint32_t)a-BITBAND_PERI_REF)*32 + (b*4))) // Convert PERI address

#define GPIOA              0x40004000
#define GPIOB              0x40005000
#define GPIOC              0x40006000
#define GPIOD              0x40007000
#define GPIOE              0x40024000
#define GPIOF              0x40025000


#define BITBAND_ACCESS(a, b)  (*(volatile uint32_t*)(((uint32_t)a & 0xF0000000) + 0x2000000 + (((uint32_t)a & 0x000FFFFF) << 5) + (b << 2)))

#define GPIOX_DATA_(a, b)     BITBAND_ACCESS((GPIO ## a _BASE) + 0x3FC, b)
#define GPIOX_DATA(a)         GPIOX_DATA_(a)


#endif /* CORE_INC_CONFIG_H_ */
