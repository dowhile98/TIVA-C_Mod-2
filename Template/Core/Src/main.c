
/*Includes -----------------------------------------------------------------------*/
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include "UART0.h"
#include "pinout.h"
#include "delay.h"
#include "config.h"
#include "PLL.h"

/*Typedef -----------------------------------------------------------------------*/


/*Macros -------------------------------------------------------------------------*/



/*Globla variables ---------------------------------------------------------------*/
uint8_t rxBuffer[100];
uint8_t txBuffer[100];
uint32_t len;

/*Function prototype --------------------------------------------------------------*/

/*Main function -------------------------------------------------------------------*/
int main(void)
{
    PLL_Config(Bus80MHz);
    Output_Init();
    len = sprintf((char*)txBuffer,"HOLA MUNDO DESDE UART0 0 TIVA C \r\n");
    UART0_SendData(txBuffer, len);
    printf("HOLA->%u\r\n",4);
    printf("HOLA->%.2f\r\n",5.9);
    UART0_Printf("PRUEBA PRINF->%.2f\r\n",3.122);

    delay_init();
    PinoutSet();

	while(1){
	     GPIOX_DATA(LED_G) ^= 1;
	     delay_ms(40);
	     GPIOX_DATA(LED_B) ^= 1;
	     delay_ms(20);
	}
}

/*Function definition --------------------------------------------------------------*/
