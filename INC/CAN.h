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
/***********************************Constants******************/
#define CAN_FIFO_0              0u
/**********************************ENUMs************************/
   /*CAN MSG*/
typedef struct 
{
    /* data */
    uint8_t data[8];
    uint8_t lower_stdid;
    uint8_t  upper_stdid;
    uint8_t dlc;

} CAN_MSG;

   
    /* CAN CFG err */
typedef enum
{
    CAN_CFG_PASSED,
    CAN_CFG_FAILED
}CAN_CFG_ERR;

/***************************************Extern data*************************/
extern CAN_MSG CAN1_MSG;
/*********************************Functions prototypes**********************/
CAN_CFG_ERR CAN1_INIT(void);
void CAN1_receive_msg(void);


#endif