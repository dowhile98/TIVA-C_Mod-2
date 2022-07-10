
/*Includes -----------------------------------------------------------------------*/
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include "UART0.h"
#include "pinout.h"
#include "delay.h"
#include "config.h"
#include "PLL.h"
#include <string.h>

/*Typedef -----------------------------------------------------------------------*/


/*Macros -------------------------------------------------------------------------*/



/*Globla variables ---------------------------------------------------------------*/
uint8_t txBuffer[100] = "HOLA MUNDO DESDE SPI0";
uint8_t rxBuffer[100];
uint32_t len;

/*Function prototype --------------------------------------------------------------*/
/**
 * @brief configura el SPI0
 */
void SPI0_Init(void);
/**
 * @brief SPI send data
 * @param pTxBuffer: Puntero a datos a transmitir
 * @param Len: Cantidad de datos a transmitir
 */
void SPI0_SendData(uint8_t *pTxBuffer, uint32_t Len);
/*Main function -------------------------------------------------------------------*/
int main(void)
{
    PLL_Config(Bus80MHz);
    Output_Init();
    delay_init();
    PinoutSet();
    SPI0_Init();
    SPI0_SendData(txBuffer, strlen((char*)txBuffer));
	while(1){
	     GPIOX_DATA(LED_G) ^= 1;
	     delay_ms(40);
	     GPIOX_DATA(LED_B) ^= 1;
	     delay_ms(20);
	}
}

/*Function definition --------------------------------------------------------------*/
void SPI0_Init(void){
    /*1. Habilitar el reloj*/
    SYSCTL_RCGCSSI_R |= 1U;
    while(!(SYSCTL_PRSSI_R & 1u));
    /*2. Deshabilitar el ssi*/
    SSI0_CR1_R &=~ (SSI_CR1_SSE);
    /*3. seleccionar el modo */
    SSI0_CR1_R &=~ (SSI_CR1_MS);
    /*4. seleccionar la fuente de reloj*/
    SSI0_CC_R = 0;
    /*5. seleecionar el prescaler*/
    //SSInClk = SysClk / (CPSDVSR * (1 + SCR))
    SSI0_CPSR_R = 4;
    SSI0_CR0_R = 9<<8;
    //CPHA
    SSI0_CR0_R &=~(SSI_CR0_SPH);
    //CPOL
    SSI0_CR0_R &=~(SSI_CR0_SPO);
    //Seleccionar el modo del protocolo
    SSI0_CR0_R &=~(SSI_CR0_FRF_M);          //moto frescale
    //data size
    SSI0_CR0_R &=~(SSI_CR0_DSS_M);
    SSI0_CR0_R |= SSI_CR0_DSS_8;
    /*7. Habilitar el periferico*/
    SSI0_CR1_R |= SSI_CR1_SSE;
}

void SPI0_SendData(uint8_t *pTxBuffer, uint32_t Len){
    uint16_t temp;
    if(pTxBuffer == NULL){
        return;
    }
    while(Len>0){
        //Esperar TNF bit
        while(!(SSI0_SR_R & SSI_SR_TNF));
        //verificar el tamaño de datos configurado
        if((SSI0_CR0_R & 0xF)>8){
            //data>8bit
            SSI0_DR_R = *((uint16_t*)pTxBuffer);

            while(!(SSI0_SR_R & SSI_SR_RNE));
            temp = SSI0_DR_R;
            Len -= 2;
            (uint16_t*)pTxBuffer++;
        }else{
            SSI0_DR_R = *pTxBuffer;
            while(!(SSI0_SR_R & SSI_SR_RNE));
            temp = SSI0_DR_R;
            pTxBuffer++;
            Len--;
        }
    }
    temp = temp;
    //esperar hasta que el SPI se libere
    while(SSI0_SR_R & SSI_SR_BSY);

    return;
}
