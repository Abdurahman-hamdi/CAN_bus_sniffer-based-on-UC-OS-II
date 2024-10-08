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
 #include  <ucos_ii.h>
/**************************************** Constants *****************************/
#define CAN_INIT_TIMEOUT_MAX	    	0xfffu
/****************************************Data defination*************************/
CAN_MSG CAN1_MSG;
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
    /* init filters */
    CAN1->FMR |= CAN_FMR_FINIT; // This bit starts Filter Initialization
    CAN1->FM1R &= ~0xFFFFFFFF;
    CAN1->FS1R &= ~0xFFFFFFFF;
    CAN1->FFA1R &= ~0xFFFFFFFF;
    CAN1->FA1R	&= ~0xFFFFFFFF;
    CAN1->sFilterRegister[0].FR1 &= ~0xFFFFFFFF; // CAN->F0R1
    CAN1->sFilterRegister[0].FR2 &= ~0xFFFFFFFF;
    CAN1->FM1R  |=  0x00; // 0 - Mask mode
    CAN1->FS1R  |=  0x01; // 1 - 32-bit
    CAN1->FFA1R |=  0x00; // 0 - FIFO 0
    CAN1->FA1R	|=  0x01;	// 1 - Active
    CAN1->sFilterRegister[0].FR1 |=  0x00; // As long as we accept all the traffic filter value is 0
    CAN1->sFilterRegister[0].FR2 |=  0x00;
    CAN1->FMR &= ~CAN_FMR_FINIT; //Filter Initialization completed
    return CAN_CFG_PASSED;
}

/**
 * @brief   CAN1_receive_msg to Handle the received msg and update the reception buffer with received msg
 * @name    CAN1_receive_msg
 * @param   none
 * @retval  none
 */
void CAN1_receive_msg(void)
{
    CAN1_MSG.lower_stdid = (CAN1->sFIFOMailBox[CAN_FIFO_0].RIR >> 21);
    CAN1_MSG.upper_stdid = (CAN1->sFIFOMailBox[CAN_FIFO_0].RIR >> 29);
    CAN1_MSG.dlc         = CAN1->sFIFOMailBox[CAN_FIFO_0].RDTR;
   if( CAN1_MSG.dlc >=1){
		CAN1_MSG.data[0]			= CAN1->sFIFOMailBox[CAN_FIFO_0].RDLR;}					 		 	 // DATA0
	if( CAN1_MSG.dlc>=2){
		CAN1_MSG.data[1]			=(CAN1->sFIFOMailBox[CAN_FIFO_0].RDLR >> 8);} 					// DATA1
	if( CAN1_MSG.dlc>=3){
		 CAN1_MSG.data[2]			=(CAN1->sFIFOMailBox[CAN_FIFO_0].RDLR >> 16);} 					// DATA2
	if( CAN1_MSG.dlc>=4){
		 CAN1_MSG.data[3]			=(CAN1->sFIFOMailBox[CAN_FIFO_0].RDLR >> 24);} 					// DATA3
	if( CAN1_MSG.dlc>=5){
		 CAN1_MSG.data[4]			= CAN1->sFIFOMailBox[CAN_FIFO_0].RDHR;} 								// DATA4
	if( CAN1_MSG.dlc>=6){
		 CAN1_MSG.data[5]			=(CAN1->sFIFOMailBox[CAN_FIFO_0].RDHR >> 8);} 					// DATA5
	if( CAN1_MSG.dlc>=7){
		 CAN1_MSG.data[6]			=(CAN1->sFIFOMailBox[CAN_FIFO_0].RDHR >> 16);} 					// DATA6
	if( CAN1_MSG.dlc==8){
		 CAN1_MSG.data[7]			=(CAN1->sFIFOMailBox[CAN_FIFO_0].RDHR >> 24);} 
}


