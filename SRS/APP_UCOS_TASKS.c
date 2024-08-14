/**
  ******************************************************************************
  * @file    APP_UCOS_TASK.h
  * @author Abdulrahman Hami
  * @version v0.1
  * @date    12-Aug-2024
  * @brief   This file contains all the functions implementation and data items to be used to build APP tasks.
  ******************************************************************************/
 /************************************************Includes**********************/
 #include"APP_UCOS_TASK.h"
 /******************************************Function definition******************/
 /**
 * @brief   CAN1_RX0_IRQHandler to Handle the received msg and notify UC_OS with the new msg
 * @name    CAN1_RX0_IRQHandler
 * @param   none
 * @retval  none
 */
void CAN1_RX0_IRQHandler(void)
{
/*needed by uc/os-ii*/
    OS_CPU_SR  cpu_sr;
    OS_ENTER_CRITICAL();   /* Tell uC/OS-II that we are starting an ISR */
    OSIntNesting++;
    OS_EXIT_CRITICAL();
    if(CAN1->RF0R & CAN_RF0R_FMP0){
		
		// And write it to the loop buffer
		if(!(CAN1->sFIFOMailBox[CAN_FIFO_0].RIR & CAN_RI0R_IDE)){ // if id is standart
		// Recieve a new message
		CAN1_receive_msg();
		}
	}

    OSIntExit(); // Tell uC/OS-II that we are leaving the ISR 
}