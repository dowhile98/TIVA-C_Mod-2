
/*Includes -----------------------------------------------------------------------*/
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include "UART0.h"
#include "pinout.h"
#include "delay.h"
#include "config.h"
#include "PLL.h"
#include <string.h>
#include "MPU6050.h"
#include "img.h"
#include "Oled.h"
#include "gui.h"
#include "test.h"

/*Typedef -----------------------------------------------------------------------*/


/*Macros -------------------------------------------------------------------------*/
#define MPU_ADD         0x68


/*Globla variables ---------------------------------------------------------------*/
uint8_t rxBuffer[100];
uint8_t txBuffer[100] = "BIENVENIDO AL BUS I2C0";
uint32_t len;

MPU6050_t MPU6050;

/*Function prototype --------------------------------------------------------------*/
/**
 * @brief inicializar el i2c0
 */
void I2C0_Init(void);

uint8_t I2C0_SendData( uint8_t SlaveAddr,uint8_t *pTxbuffer, uint32_t Len);

uint8_t I2C0_ReceiveData( uint8_t SlaveAddr,uint8_t *pRxbuffer, uint32_t Len);

uint8_t I2C0_WriteRegister(uint8_t SlaveAddr, uint8_t reg, uint8_t val);

uint8_t I2C0_ReadRegister(uint8_t SlaveAdrr, uint8_t reg, uint8_t *pData);



/*Main function -------------------------------------------------------------------*/
int main(void)
{
    PLL_Config(Bus80MHz);
    Output_Init();
    delay_init();
    PinoutSet();

    I2C0_Init();

//    I2C0_SendData(MPU_ADD, txBuffer, strlen((char*)txBuffer));
//    txBuffer[0] = 0x3A;
//    I2C0_SendData(MPU_ADD, txBuffer, 1);
//    I2C0_ReceiveData(MPU_ADD, rxBuffer, 10);
    if (MPU6050_Init(&MPU6050, MPU6050_Device_0, MPU6050_Accelerometer_8G, MPU6050_Gyroscope_250s) == MPU6050_Result_Ok) {
        /* Green LED on */
        GPIOX_DATA(LED_G) = 1;
    }
    delay_ms(1000);
    OLED_Init();
    OLED_Clear(1);
    TEST_BMP();
    delay_ms(1000);
    Test_Rectangular();
    delay_ms(1000);
    Test_Circle();
    delay_ms(1000);
    Test_Triangle();
	while(1){
	    MPU6050_ReadAll(&MPU6050);
        GPIOX_DATA(LED_B) ^= 1U;
        GUI_DrawBMP(0, 0, pajaro.width, pajaro.height, (uint8_t*)pajaro.data, 1);
        delay_ms(2000);
        GUI_DrawBMP(0, 0, pajaro.width, pajaro.height, (uint8_t*)pajaro.data, 0);
        delay_ms(2000);
	}
}

/*Function definition --------------------------------------------------------------*/
void I2C0_Init(void){
    /*Habilitar el reloj*/
    SYSCTL_RCGCI2C_R |= 1U;
    while(!(SYSCTL_PRI2C_R & 0x1));
    /*Habilitamos el modo maestro*/
    I2C0_MCR_R |= I2C_MCR_MFE;
    /*Configurar la frecuencia de transmision*/
    //TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
    // TPR = 80MHz/(2*10*400000) - 1
    // TPR = 9
    I2C0_MTPR_R = 9;

    return;
}

uint8_t I2C0_SendData( uint8_t SlaveAddr,uint8_t *pTxbuffer, uint32_t Len){
    uint8_t temp;
    //escribir la direccion del esclavo
    I2C0_MSA_R = SlaveAddr<<1;
    I2C0_MSA_R &=~ (1U);                //WRITE OPERATION

    if(Len == 1){
        I2C0_MDR_R = *pTxbuffer & 0xFFU;
        while(I2C0_MCS_R & I2C_MCS_BUSY);
        //iniciar la comunicacion
        I2C0_MCS_R = I2C_MCS_RUN | I2C_MCS_START | I2C_MCS_STOP;
        while(I2C0_MCS_R & I2C_MCS_BUSY);
        temp = I2C0_MCS_R & 0xE;
        if(temp != 0){
            return temp;
        }
        return 0;
    }else{
        I2C0_MDR_R = *pTxbuffer & 0xFFU;
        pTxbuffer++;
        Len--;
        while(I2C0_MCS_R & I2C_MCS_BUSY);
        //iniciar la comunicacion
        I2C0_MCS_R = I2C_MCS_RUN | I2C_MCS_START;

        while(I2C0_MCS_R & I2C_MCS_BUSY);
        temp = I2C0_MCS_R & 0xE;
        if(temp != 0){
            return temp;                                //retorna un error en a comunicacion
        }
    }
    //enviar los datos restantes
    while(Len>0){
        if(Len == 1){
            I2C0_MDR_R = *pTxbuffer & 0xFFU;
            while(I2C0_MCS_R & I2C_MCS_BUSY);
            //iniciar la comunicacion
            I2C0_MCS_R = I2C_MCS_RUN  | I2C_MCS_STOP;
            while(I2C0_MCS_R & I2C_MCS_BUSY);
            temp = I2C0_MCS_R & 0xE;
            if(temp != 0){
                return temp;
            }
            Len--;
            pTxbuffer++;
        }else{
            I2C0_MDR_R = *pTxbuffer & 0xFFU;
            I2C0_MCS_R = I2C_MCS_RUN;
            //eperar
            while(I2C0_MCS_R & I2C_MCS_BUSY);
            temp = I2C0_MCS_R & 0xE;
            if(temp != 0){
                return temp;
            }
            pTxbuffer++;
            Len--;
        }
    }
    return 0;
}

uint8_t I2C0_ReceiveData( uint8_t SlaveAddr,uint8_t *pRxbuffer, uint32_t Len){
    uint8_t temp;
    //enviar la direccion del esclavo
    I2C0_MSA_R = SlaveAddr<<1;
    I2C0_MSA_R |= 1U;
    //esperar que el bus se libere
    while(I2C0_MCS_R & I2C_MCS_BUSY);
    //generar la condicion de inicio y se lee el primer byte
    if(Len == 1){
        I2C0_MCS_R = I2C_MCS_RUN | I2C_MCS_STOP | I2C_MCS_START;
        while(I2C0_MCS_R & I2C_MCS_BUSY);
        temp = I2C0_MCS_R & 0xE;
        if(temp != 0){
            return temp;
        }
        *pRxbuffer = I2C0_MDR_R & 0xFFU;

    }else{
        I2C0_MCS_R = I2C_MCS_RUN | I2C_MCS_START | I2C_MCS_ACK;
        while(I2C0_MCS_R & I2C_MCS_BUSY);
        temp = I2C0_MCS_R & 0xE;
        if(temp != 0){
            return temp;
        }
        *pRxbuffer = I2C0_MDR_R & 0xFFU;
        pRxbuffer++;
        Len--;
    }

    while(Len>0){
        if(Len == 1){
            I2C0_MCS_R = I2C_MCS_RUN | I2C_MCS_STOP;
            while(I2C0_MCS_R & I2C_MCS_BUSY);
            temp = I2C0_MCS_R & 0xE;
            if(temp != 0){
                return temp;
            }
            *pRxbuffer = I2C0_MDR_R & 0xFFU;
            Len--;
        }else{
            I2C0_MCS_R = I2C_MCS_RUN  | I2C_MCS_ACK;
            while(I2C0_MCS_R & I2C_MCS_BUSY);
            temp = I2C0_MCS_R & 0xE;;
            if(temp != 0){
                return temp;
            }
            *pRxbuffer = I2C0_MDR_R & 0xFFU;
            pRxbuffer++;
            Len--;
        }
    }
    return 0;
}
uint8_t I2C0_WriteRegister(uint8_t SlaveAddr, uint8_t reg, uint8_t val){
    uint8_t temp;
    //escribimos la direccino del esclavo
    //write
    I2C0_MSA_R = SlaveAddr<<1U;
    I2C0_MSA_R &=~ (1U);
    I2C0_MDR_R = reg;
    while(I2C0_MCS_R & I2C_MCS_BUSY);

    //se genera la condicion de inicio
    I2C0_MCS_R = I2C_MCS_RUN | I2C_MCS_START;
    while(I2C0_MCS_R & I2C_MCS_BUSY);
    temp = I2C0_MCS_R & 0xE;;
    if(temp != 0){
        return temp;
    }

    I2C0_MDR_R = val;
    while(I2C0_MCS_R & I2C_MCS_BUSY);

    //se genera la condicion de inicio
    I2C0_MCS_R = I2C_MCS_RUN | I2C_MCS_STOP;
    while(I2C0_MCS_R & I2C_MCS_BUSY);
    temp = I2C0_MCS_R & 0xE;;
    if(temp != 0){
        return temp;
    }
    return temp;

}

uint8_t I2C0_ReadRegister(uint8_t SlaveAddr, uint8_t reg, uint8_t *pData){
    uint8_t temp;
    //write
    I2C0_MSA_R = SlaveAddr<<1U;
    I2C0_MSA_R &=~ (1U);
    I2C0_MDR_R = reg;
    while(I2C0_MCS_R & I2C_MCS_BUSY);

    //se genera la condicion de inicio
    I2C0_MCS_R |= I2C_MCS_RUN | I2C_MCS_START;
    while(I2C0_MCS_R & I2C_MCS_BUSY);
    temp = I2C0_MCS_R & 0xE;
    if(temp != 0){
        return temp;
    }
    //read
    I2C0_MSA_R = SlaveAddr<<1U;
    I2C0_MSA_R |= 1U;
    while(I2C0_MCS_R & I2C_MCS_BUSY);
    //repeated start condition
    I2C0_MCS_R = I2C_MCS_RUN | I2C_MCS_START | I2C_MCS_STOP;
    while(I2C0_MCS_R & I2C_MCS_BUSY);
    temp = I2C0_MCS_R & 0xE;;
    if(temp != 0){
        return temp;
    }
    *pData = I2C0_MDR_R;
    return 0;
}
