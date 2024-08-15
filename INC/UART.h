/**
  ******************************************************************************
  * @file    UART.h
  * @author Abdulrahman Hami
  * @version v0.1
  * @date    12-Aug-2024
  * @brief   This file contains all the functions prototypes to be used to init UART App.
  ******************************************************************************/

#ifndef __UART_H_
#define __UART_H_
/**************************************ENUMs **********************************/

typedef enum
{
    UART_TX_PASSED,
    UART_TX_FAILED
}UARTTX_STATUS;
/*************************************Includes ********************************/
#include"GPIO.h"
/*********************************Functions prototypes***************************/
void USART3_Init(void);
UARTTX_STATUS USART3_char_Transmit(uint8_t data);
UARTTX_STATUS USART3_string_Transmit(uint8_t*);





#endif