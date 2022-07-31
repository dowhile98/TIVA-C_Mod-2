/*
 * UART0.h
 *
 *  Created on: 5 mar. 2022
 *      Author: Lenovo
 */

#ifndef CORE_INC_UART0_H_
#define CORE_INC_UART0_H_
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

#define LENGTH(ARRAY)   ((sizeof(ARRAY)/sizeof(*(ARRAY))) - 1U)

#define SYSCLK      16E+6
#define BAUDS       115200

#define __GET_IBRD(UARTSysClk, ClkDiv, BaudRate)      ((uint16_t)(UARTSysClk/(ClkDiv*BaudRate)))
#define __GET_FRACPART(UARTSysClk, ClkDiv, BaudRate)  ((float)UARTSysClk/(ClkDiv*BaudRate) - __GET_IBRD(UARTSysClk, ClkDiv, BaudRate) )
#define __GET_FBRD(UARTSysClk, ClkDiv, BaudRate)      ((uint8_t)(  __GET_FRACPART(UARTSysClk, ClkDiv, BaudRate) * 64 + 0.5  ))

//------------UART_Init------------
// Initialize the UART for 115,200 baud rate (assuming 80 MHz clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART0_Config(uint32_t uartSysClk, uint32_t baud);

/**
 * @brief funcion que envia serie de bytes por el uart0
 */
void UART0_SendData(uint8_t *pTxData,uint32_t Len);
/**
 * @brief funcion que recibe una serie de bytes por el UART0
 */
void UART0_ReceiveData(uint8_t *pRxData,uint32_t Len);

/**
 * @brief envio de datos con formato
 */

void UART0_Printf(char *format,...);
/**
 * @brief configura el UART0 para el printf
 */
void Output_Init(void);

/*
 * IRQ Configuration and ISR handling
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
//void USART_IRQHandling(USART_Handle_t *pUSARTHandle);

/*
 * Application Callbacks
 */
//void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t ApEv);

#endif /* CORE_INC_UART0_H_ */
