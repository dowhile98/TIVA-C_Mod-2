
/*Includes -----------------------------------------------------------------------*/
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include "UART0.h"
#include "pinout.h"
#include "delay.h"
#include "config.h"
#include "PLL.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
/*Typedef -----------------------------------------------------------------------*/


/*Macros -------------------------------------------------------------------------*/



/*Globla variables ---------------------------------------------------------------*/
uint8_t rxBuffer[100];
uint8_t txBuffer[100];
uint32_t len;

TaskHandle_t task1_handler;
TaskHandle_t task2_handler;

SemaphoreHandle_t xSemaphore = NULL;

/*Function prototype --------------------------------------------------------------*/

void task1(void *params);

void task2(void *params);

/*Main function -------------------------------------------------------------------*/
int main(void)
{
    BaseType_t status;
    //PLL_Config(Bus80MHz);
    Output_Init();
    //delay_init();
    PinoutSet();

    //CREACION DE TAREAS
    status = xTaskCreate(task1,
                         "tarea 1",
                         256,
                         NULL, 1,
                         &task1_handler);
    configASSERT(status == pdPASS);

    status = xTaskCreate(task2,
                             "tarea 2",
                             256,
                             NULL, 1,
                             &task2_handler);
    configASSERT(status == pdPASS);

    xSemaphore = xSemaphoreCreateMutex();

    //iniciar el kerner RTOS
    vTaskStartScheduler();

	while(1){

	}
}

/*Function definition --------------------------------------------------------------*/

void task1(void *params){

    while(1){
        //printf("HOLA MUNDO DESDE TAREA 1\r\n");
        if(xSemaphoreTake( xSemaphore, portMAX_DELAY ) == pdTRUE){

            UART0_Printf("HOLA MUNDO DESDE TAREA 1\r\n");

            xSemaphoreGive( xSemaphore );
        }

        GPIOX_DATA(LED_B) ^= 1U;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task2(void *params){
    while(1){
        //printf("HOLA MUNDO DESDE TAREA 2\r\n");
        if(xSemaphoreTake( xSemaphore, portMAX_DELAY ) == pdTRUE){

            UART0_Printf("HOLA MUNDO DESDE TAREA 2\r\n");

            xSemaphoreGive( xSemaphore );
        }
        GPIOX_DATA(LED_G) ^= 1U;
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}
