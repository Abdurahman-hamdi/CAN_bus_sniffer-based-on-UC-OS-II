/**
  ******************************************************************************
  * @file    APP_UCOS_TASK.h
  * @author Abdulrahman Hami
  * @version v0.1
  * @date    12-Aug-2024
  * @brief   This file contains all the functions prototypes to be used to build APP tasks.
  ******************************************************************************/
#ifndef __APP_TASH_
#define __APP_TASH_
/**************************************Includes*********************************/
#include"UART.h"
#include"CAN.h"
#include "ucos_ii.h"
/****************************************Function prototype********************/
void APP_system_init(void);
void App_system_run(void);
#endif