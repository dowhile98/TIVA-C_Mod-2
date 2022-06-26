/*
 * UART0.c
 *
 *  Created on: 5 mar. 2022
 *      Author: Lenovo
 */


#include "UART0.h"

//------------UART_Init------------
// Initialize the UART for 115,200 baud rate (assuming 80 MHz clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART0_Config(uint32_t uartSysClk, uint32_t baud){
    /*CONFIGURAR LOS PINES RELACIONADOR CON EL UART0*/
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
    while(!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0));       //GPIO LISTO
    GPIO_PORTA_AFSEL_R |= 1<<1 | 1<<0;                 //PA0, PA1 funcion alternativa
    GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX;
    GPIO_PORTA_DEN_R |= 1<<1 | 1<<0;

    /*CONFIGURACION DE LOS PARAMETROS DEL UART0*/
    SYSCTL_RCGC1_R|= SYSCTL_RCGC1_UART0;
    while(!(SYSCTL_PRUART_R & SYSCTL_PRUART_R0));
    /*deshabilitar el uart0*/
    UART0_CTL_R &=~ UART_CTL_UARTEN;
    /*configurar los baudios*/
    UART0_IBRD_R = __GET_IBRD(uartSysClk,16,baud);
    UART0_FBRD_R = __GET_FBRD(uartSysClk,16,baud);
    /*configurar los parametros deseados para el uart*/
    UART0_LCRH_R |= UART_LCRH_WLEN_8;
    /*configurar la fuente de reloj para el uart0*/
    UART0_CC_R &= UART_CC_CS_SYSCLK;

    /***************SE HABILITA EL UART0***************************/
    UART0_CTL_R |= UART_CTL_UARTEN;
}



/**
 * @brief funcion que envia serie de bytes por el uart0
 */
void UART0_SendData(uint8_t *pTxData,uint32_t Len){
    uint16_t *pdata;
    uint32_t i;
    for(i=0 ;i<Len;i++){
        //verificar el flag TXFF
        while(!(UART0_FR_R & UART_FR_TXFE));
        //verificar si se va transmitir en modo de 8bit o 9 bit
        if(UART0_9BITADDR_R & UART_9BITADDR_9BITEN){
            //code here
            pdata = (uint16_t*)pTxData;
            UART0_DR_R = (*pdata) & 0x1FF;
            //verificar la paridad
            if(!(UART0_LCRH_R & UART_LCRH_PEN)){
                (uint16_t*)pTxData++;
            }else{
                pTxData++;
            }
        }else{
            //modo de 8 bit
            UART0_DR_R = (*pTxData) & 0xFF;
            pTxData++;
        }
    }
    //Esperar que se termine de transmitir los datos
    while(UART0_FR_R & UART_FR_BUSY);

    return;
}
/**
 * @brief funcion que recibe una serie de bytes por el UART0
 */
void UART0_ReceiveData(uint8_t *pRxData,uint32_t Len){
    uint32_t i;
    for( i= 0;i<Len;i++){
        //verificar el flag RXFE
        while(UART0_FR_R & UART_FR_RXFE);
        //verificar si se va recibir en modo de 8bit o 9bit
        if(UART0_9BITADDR_R & UART_9BITADDR_9BITEN){
            //VERIFICAR LA PARIDAD
            if(!(UART0_LCRH_R & UART_LCRH_PEN)){
                *((uint16_t*)pRxData) = UART0_DR_R & 0x1FF;
                (uint16_t*)pRxData++;
            }else{
                *pRxData = UART0_DR_R & (uint8_t)0xFF;
                pRxData++;
            }
        }else{
            /*VERIFICAR LA PARIDAD*/
            if(!(UART0_LCRH_R & UART_LCRH_PEN)){
                *pRxData = UART0_DR_R & (uint8_t)0xFF;
            }else{
                *pRxData = UART0_DR_R & (uint8_t)0x7F;
            }
            pRxData++;
        }
    }
    return;
}


void UART0_Printf(char *format,...){
    char str[80];

    /*Extract the the argument list using VA apis */
    va_list args;
    va_start(args, format);
    vsprintf(str, format,args);

    UART0_SendData((uint8_t*)str, strlen(str) );
    va_end(args);
}
/*************************************************************************************************/
uint8_t UART0_Receive(void){

    while((UART0_FR_R & UART_FR_RXFE)!=0);
    return UART0_DR_R;
}


void UART0_Transmit(uint8_t ch){
    while((UART0_FR_R & UART_FR_TXFF)!=0);  // si la FIFO esta lleno
    UART0_DR_R = ch;                        //se envía un caracter
}

#ifdef __TI_COMPILER_VERSION__
    //Code Composer Studio Code
#include "file.h"
int uart_open(const char *path, unsigned flags, int llv_fd){
  UART0_Config(SYSCLK, BAUDS);
  return 0;
}
int uart_close( int dev_fd){
    return 0;
}
int uart_read(int dev_fd, char *buf, unsigned count){char ch;
  ch = UART0_Receive();    // receive from keyboard
  ch = *buf;         // return by reference
  UART0_Transmit(ch);  // echo
  return 1;
}
int uart_write(int dev_fd, const char *buf, unsigned count){ unsigned int num=count;
    while(num){
        UART0_Transmit(*buf);
        buf++;
        num--;
    }
    return count;
}
off_t uart_lseek(int dev_fd, off_t ioffset, int origin){
    return 0;
}
int uart_unlink(const char * path){
    return 0;
}
int uart_rename(const char *old_name, const char *new_name){
    return 0;
}

//------------Output_Init------------
// Initialize the UART for 115,200 baud rate (assuming 3 MHz bus clock),
// 8 bit word length, no parity bits, one stop bit
// Input: none
// Output: none
void Output_Init(void){
    int ret_val; FILE *fptr;
    UART0_Config(SYSCLK, BAUDS);
    ret_val = add_device("uart", _SSA, uart_open, uart_close, uart_read, uart_write, uart_lseek, uart_unlink, uart_rename);
    if(ret_val)
        return; // error
    fptr = fopen("uart","w");
    if(fptr == 0)
        return; // error
    freopen("uart:", "w", stdout); // redirect stdout to uart
    setvbuf(stdout, NULL, _IONBF, 0); // turn off buffering for stdout

}
#else
//Keil uVision Code
//------------Output_Init------------
// Initialize the Nokia5110
// Input: none
// Output: none
//------------Output_Init------------
// Initialize the UART for 115,200 baud rate (assuming 16 MHz bus clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none

#endif
