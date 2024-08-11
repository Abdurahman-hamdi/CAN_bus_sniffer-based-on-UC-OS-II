/**
  ******************************************************************************
  * @file    CAN.h
  * @author Abdulrahman Hami
  * @version v0.1
  * @date    12-Aug-2024
  * @brief   This file contains all the functions prototypes to be used to init CAN TXRX Application .
  ******************************************************************************/

#ifndef __CAN_H_
#define __CAN_H_
/***********************************Includes********************/
#include"GPIO.h"
/**********************************ENUMs************************/
    /* CAN CFG err */
typedef enum
{
    CAN_CFG_PASSED,
    CAN_CFG_FAILED
}CAN_CFG_ERR;

/*********************************Includes**********************/
CAN_CFG_ERR CAN1_INIT(void);


#endif