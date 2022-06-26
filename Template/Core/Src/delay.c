/*
 * delay.c
 *
 *  Created on: 25 jun. 2022
 *      Author: jeffr
 */
#include "delay.h"

/**
 * @brief inicializar el systick
 */
void delay_init(void){
    uint32_t temp;
    temp = SYSCLK / 1000;
    /*establecer el valor de autorecarga*/
    NVIC_ST_RELOAD_R = temp - 1;
    /*Seleccionar la fuente de reloj del systick*/
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;
    /*habilitamos el conteo*/
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
    return;
}
/**
 * @brief generar retardos en ms
 * @param time_ms: retardo deseado
 */
void delay_ms(uint32_t time_ms){
    uint32_t i;
    /*reiniciar el valor del conteo actual*/
    NVIC_ST_CURRENT_R = 0;
    /*generar el retardo*/
    for(i = 0;i<time_ms; i++){
        while(!(NVIC_ST_CTRL_R & 1U<<16));      //GENERA UN RETARDO DE 1ms
    }
    return;
}

