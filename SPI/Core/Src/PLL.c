/*
 * PLL.c
 *
 *  Created on: 13 mar. 2022
 *      Author: Lenovo
 */


#include "PLL.h"

uint32_t SystemCoreClock;
/**
  * @fn PLL_Config
  * @brief configura  el systemCoreClock
  * @param freq: frecuencia de referencia deseada
  */
void PLL_Config(uint32_t freq){
    /*establecer el bit USERCC2 para usar el registro RCC2*/

    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
    /*1. cambiar la fuente del sysctl*/
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
    /*2. Seleccionar la fuente del pll y establecer la frecuencia*/

    SYSCTL_RCC_R &=~ SYSCTL_RCC_XTAL_M;
    SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ;
    SYSCTL_RCC2_R &=~ SYSCTL_RCC2_OSCSRC2_M;
      /*3. Encender el PLL*/
    SYSCTL_RCC2_R &=~ SYSCTL_RCC2_PWRDN2;
      /*4. establecer los valores de SYSDIV2 Y SYSDIVLSB*/
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;
    SYSCTL_RCC2_R &=~ (SYSCTL_RCC2_SYSDIV2_M | SYSCTL_RCC2_SYSDIV2LSB);
    SYSCTL_RCC2_R |= freq<<22;
    /*5. Esperar que el PLL este listo para ser usado*/
    while(!(SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS));
    /*6. Seleccionar el pll como fuente de reloj*/
    SYSCTL_RCC2_R &=~ SYSCTL_RCC2_BYPASS2;
    /**************************************************************************/
    SystemCoreClock = SysCtlClockGet();
    return;
}

