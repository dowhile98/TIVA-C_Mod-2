/*
 * delay.h
 *
 *  Created on: 25 jun. 2022
 *      Author: jeffr
 */

#ifndef CORE_INC_DELAY_H_
#define CORE_INC_DELAY_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>


#define SYSCLK              16E+6
/**
 * @brief inicializar el systick
 */
void delay_init(void);
/**
 * @brief generar retardos en ms
 * @param time_ms: retardo deseado
 */
void delay_ms(uint32_t time_ms);

#endif /* CORE_INC_DELAY_H_ */
