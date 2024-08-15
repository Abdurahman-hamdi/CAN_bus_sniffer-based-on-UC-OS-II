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
 /******************************************* static data***********************/
 /*create semaphore with 0 or locked initial state */
	static  OS_EVENT *TX_IT_SYNC_semaphore;
    static OS_STK stk1_prio10[1000];
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
        OSSemPost(TX_IT_SYNC_semaphore);
		}
	}

    OSIntExit(); // Tell uC/OS-II that we are leaving the ISR 
}
/**
 * @brief   Define UCOS-II task to transmit the recived can message .
 * @name    USB_transmit_task
 * @param   void*pdata
 * @retval  void
 */
static void USB_transmit_task(void*pdata)
{   int err;
    pdata=pdata;
    while (1)
    {
        OSSemPend(TX_IT_SYNC_semaphore,0,&err);
        USART3_string_Transmit("hello");
    }
    
}
/**
 * @brief   APP_system_init is to initialize  the App.
 * @name    APP_system_init
 * @param   void
 * @retval  void
 */
void APP_system_init(void)
{
    OSInit();//init UCOSII
    TX_IT_SYNC_semaphore=OSSemCreate(0);
    OSTaskCreate (USB_transmit_task,(void*)0,&stk1_prio10[999],1);//create USB_transmit_task app task
    USART3_GPIO_Config();//init usart3_gpio
    CAN1_GPIO_config();//init can1_gpio
    USART3_Init();//init usart3
    CAN1_INIT();//init can1
    OSStart();


}