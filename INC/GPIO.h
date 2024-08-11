/**
  ******************************************************************************
  * @file    GPIO.h
  * @author Abdulrahman Hami
  * @version v0.1
  * @date    12-Aug-2024
  * @brief   This file contains all the functions prototypes to be used to init GPIO drivers for CAN and UART.
  ******************************************************************************/

#ifndef __GPIO_H_
#define __GPIO_H_

/************************************Includes*************************************/
#include <stddef.h>
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include"stm32f4xx_gpio.h"
#include"stm32f4xx_can.h"
/*********************************Functions prototypes***************************/
    
void CAN1_GPIO_config(void);   
void USART3_GPIO_Config(void);
#endif