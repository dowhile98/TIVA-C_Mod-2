
/*Includes -----------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <inc/tm4c123gh6pm.h>

#include "UART0.h"
#include "pinout.h"
#include "delay.h"
#include "config.h"
#include "PLL.h"

/*Typedef -----------------------------------------------------------------------*/


/*Macros -------------------------------------------------------------------------*/
#define CH30        30 * 4
#define SIZE        128

/*Globla variables ---------------------------------------------------------------*/
#if defined(ewarm)                              //IAR
#pragma data_alignment=1024
uint8_t ui8ControlTable[1024];
#elif defined(ccs)
#pragma DATA_ALIGN(ui8ControlTable, 1024)       //CCS
uint8_t ui8ControlTable[1024];
#else
uint8_t ui8ControlTable[1024] __attribute__ ((aligned(1024)));
#endif

uint32_t SrcBuf[SIZE];                          //La fuente
uint32_t DestBuf[SIZE];                         //Destino

/*Function prototype --------------------------------------------------------------*/

/*Main function -------------------------------------------------------------------*/
int main(void)
{
    uint32_t i;
    PLL_Config(Bus80MHz);
    Output_Init();
    delay_init();


    for(i = 0;i<SIZE;i++){
        SrcBuf[i] = rand() * 20;
        DestBuf[i] = 0;
    }
    //MODULO (Configuracion general)
    /*1. Habilitar el reloj*/
    SYSCTL_RCGCDMA_R |= SYSCTL_RCGCDMA_R0;
    while(!(SYSCTL_PRDMA_R & 1U));
    /*2. habilitar el bit MASTEREN*/
    UDMA_CFG_R |= UDMA_CFG_MASTEN;
    /*3. Establecer la direccion del control table*/
    UDMA_CTLBASE_R = (uint32_t)ui8ControlTable;

    //Configuracion del canal (Memoria a memoria)
    /*1. configurar la prioridad*/
    UDMA_PRIOCLR_R |= 1U<<30;
    /*2. Seleccionar el bloque de control*/
    UDMA_ALTCLR_R |= 1U<<30;
    /*3. seleccionar el tipo de solicitud*/
    UDMA_USEBURSTCLR_R |= 1U<<30;
    /*4. El reconocimiento de la solicitud*/
    UDMA_REQMASKCLR_R |= 1U<<30;
    //CONFIGURAR el control Table
    ((uint32_t*)ui8ControlTable)[CH30] = (uint32_t)(SrcBuf) + SIZE*4 - 1;
    ((uint32_t*)ui8ControlTable)[CH30 + 1] = (uint32_t)(DestBuf) + SIZE*4 - 1;
    ((uint32_t*)ui8ControlTable)[CH30 + 2] = 0xAA00C002 + ((SIZE - 1)<<4);
    //iniciar la transferencia
    UDMA_ENASET_R |= 1U<<30;
    UDMA_SWREQ_R |= 1U<<30;

    PinoutSet();
	while(1){
	     GPIOX_DATA(LED_G) = 0;
	     delay_ms(40);
	     GPIOX_DATA(LED_B) ^= 1;
	     delay_ms(20);
	}
}

/*Function definition --------------------------------------------------------------*/
