/**
  ******************************************************************************
  * @file    CAN.c
  * @author Abdulrahman Hami
  * @version v0.1
  * @date    12-Aug-2024
  * @brief   This file contains all the functions prototypes to be used to init CAN TXRX Application .
  ******************************************************************************/

 /************************************** Includes *******************************/
 #include"CAN.h"
/**************************************** Constants *****************************/
#define CAN_INIT_TIMEOUT_MAX	    	0xfffu
/****************************************Functions implementation**************/
 /**
 * @brief   CAN1_INIT  which configures CAN1 as receiver with 500b/s and init the filteration.
 * @name    CAN1_INIT
 * @param   none
 * @retval  CAN_CFG_ERR =passed when it is being configured correctly
 *          CAN_CFG_ERR =Failed when it is not being configured correctly
 */
CAN_CFG_ERR CAN1_INIT(void)
{
    /* Define timeout cnt to watch the init process timeout*/
    uint32_t timeout=0u;                    
    /* Enable peripheral clock*/
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;	
    /*Enter init mode*/
    CAN1->MCR |= CAN_MCR_INRQ;
    /*Quitting Sleep mode*/	
    CAN1->MCR &= ~CAN_MCR_SLEEP;
    
	while(!(CAN1->MSR & CAN_MSR_INAK) && (timeout < CAN_INIT_TIMEOUT_MAX)){
		timeout++;	// Waiting for a flag CAN_MSR_INAK (This means, Initialization mode started)
	};
	if(!(CAN1->MSR & CAN_MSR_INAK)){ // If a timeout passed away and CAN_MSR_INAK had not come up - Error
		return CAN_CFG_FAILED;
	}
    /* setting the baudrate to oprate at 500kbps*/
    CAN1->BTR &= ~CAN_BTR_TS1; // reset value
	CAN1->BTR &= ~CAN_BTR_TS2; // reset value
	CAN1->BTR &= ~CAN_BTR_SJW; // reset value
	CAN1->BTR |= 0x0003u;       //Prescaler
	CAN1->BTR |= (0x0A << 16); //BS1
	CAN1->BTR |= (0x05 << 20); //BS2

    /* Enabling reception pending interrupt*/
    CAN1->IER |= CAN_IER_FMPIE0;
    /*Enable auto recovery out from Buss-off*/
    CAN1->MCR |= CAN_MCR_ABOM;
    /* Quit init mode*/
    CAN1->MCR &= ~CAN_MCR_INRQ;
    /* Reset timeout*/
    timeout=0;
	while((CAN1->MSR & CAN_MSR_INAK) && (timeout < CAN_INIT_TIMEOUT_MAX)){
		timeout++;
	}; // Waiting for both CAN_MSR_SLAK and CAN_MSR_INAK flags down(This means, Normal mode started)

	if((!(CAN1->MSR & CAN_MSR_INAK)) && (!(CAN1->MSR & CAN_MSR_SLAK))){
	//Check SLAK and INAK flags. If they are reset, Controller has entered normal mode
		return CAN_CFG_FAILED;
	}
    return CAN_CFG_PASSED;
}