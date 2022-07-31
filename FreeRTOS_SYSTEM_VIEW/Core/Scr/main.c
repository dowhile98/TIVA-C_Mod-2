
/**
 * main.c
 */
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include "core_cm4.h"
#include <stdio.h>
/*macros*/
#define SEGGER_SYSTEM_VIEW      1


/*variables globales*/
TaskHandle_t task1Handle;
TaskHandle_t task2Handle;
TaskHandle_t task3Handle;
SemaphoreHandle_t semButton = NULL;

uint8_t txbuffer[100];

/*prototipo de funciones*/
void task1(void *params);
void task2(void *params);
void task3(void *params);

/**
  * @brief configura los pines necesarios
  */
void GPIOF_Config(void);

int main(void)
{
    uint8_t status;
    /*GPIO Init*/
    GPIOF_Config();
/********************************************************************************/
#if SEGGER_SYSTEM_VIEW
    DWT->CTRL |= 1;
    SEGGER_SYSVIEW_Conf();
#endif
/*******************************************************************************/
    semButton = xSemaphoreCreateBinary();
    /*tasks create*/
    status = xTaskCreate(task1, "Tarea 1", configMINIMAL_STACK_SIZE, "TAREA 1", 2, &task1Handle);
    configASSERT(status == pdPASS);

    status = xTaskCreate(task2, "Tarea 2", configMINIMAL_STACK_SIZE, "TAREA 2", 2, &task2Handle);
    configASSERT(status == pdPASS);

    status = xTaskCreate(task3, "Tarea 3", configMINIMAL_STACK_SIZE, "TAREA 3", 2, &task3Handle);
    configASSERT(status == pdPASS);

    /*os start*/
    vTaskStartScheduler();

    while(1){

    }
}
/**
  * @brief configura los pines necesarios
  */
void GPIOF_Config(void){
  /*1. habilitar el reloj y esperar que este listo*/
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;

  while(!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5));
  /*2. unlock*/
  GPIO_PORTF_LOCK_R = 0x4C4F434B;

  GPIO_PORTF_CR_R = 0x1;
  /*3. Configurar la direccion*/
  //PF1, PF2, PF3 -> SALIDA
  GPIO_PORTF_DIR_R |= 1U<<3 | 1U<<2 | 1U<<1;
  //PF0, PF4 -> ENTRADA
  GPIO_PORTF_DIR_R &=~ (1U<<4 | 1U<<0); // GPIOF->DIR = GPIOF->DIR & (~(0x10 | 0x1));
                                  // GPIOF->DIR = GPIOF->DIR & (0xEF | 0xE)
  GPIO_PORTF_PUR_R |= 1U<<4 | 1U<<0;    //pull up

  /*4. habilitar la funcion digital*/
  GPIO_PORTF_DEN_R |= 1U<<4 | 1U<<3 | 1U<<2 | 1U<<1 | 1U<<0; //0x1F
  return;
}
/*definicion de funciones*/
void task1(void *params){

    while(1){
#if SEGGER_SYSTEM_VIEW
        SEGGER_SYSVIEW_PrintfTarget("tarea 1\r\n");
#endif
        GPIO_PORTF_DATA_R ^= 1U<<1;
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}
void task2(void *params){

    while(1){
        if(xSemaphoreTake(semButton,portMAX_DELAY)){

#if SEGGER_SYSTEM_VIEW
        SEGGER_SYSVIEW_PrintfTarget("semaforo recibido\r\n");
#endif
        GPIO_PORTF_DATA_R ^= 1U<<2;
        }
        else{
#if SEGGER_SYSTEM_VIEW
        SEGGER_SYSVIEW_PrintfTarget("semaforo no recibido\r\n");
#endif
        }
    }
}

void task3(void *params){
    while(1){
        if(!(GPIO_PORTF_DATA_R & 1<<4)){

#if SEGGER_SYSTEM_VIEW
        SEGGER_SYSVIEW_PrintfTarget("semaforo enviado\r\n");
#endif
        xSemaphoreGive(semButton);
        vTaskDelay(pdMS_TO_TICKS(500));
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
/************************************************************************************/

