/**
  ******************************************************************************
  * @file    UART.c
  * @author Abdulrahman Hami
  * @version v0.1
  * @date    12-Aug-2024
  * @brief   This file contains all the functions implementation to be used to init UART App.
  ******************************************************************************/
 /************************************** Includes *******************************/
 #include"UART.h"
 #include"CAN.h"
 /************************************** Constants ******************************/
 #define UARTTX_TIMEOUT_MAX               0xffu
 /**************************************Functions implementation*****************/

 /**
 * @brief   USART3_Init  which configures USART3 as TX with  38.4kbs as buadrate.
 * @name    USART3_Init
 * @param   none
 * @retval  none
 */
 void USART3_Init(void)
 {
    /* Enable USART3 clock */
	RCC->APB1ENR = RCC_APB1ENR_USART3EN;
    /* Select oversampling by 8 mode */
	USART3->CR1 &= ~USART_CR1_OVER8;
	/* Select one sample bit method */
	USART3->CR3 |= USART_CR3_ONEBIT;
	/* Select 1 Start bit, 8 Data bits, n Stop bit */
	USART3->CR1 &= ~USART_CR1_M;
	/* Select 1 stop bit */
	USART3->CR2 &= ~USART_CR2_STOP;
	/* disable parity control */
    	USART3->CR1 &= ~USART_CR1_PCE;

	//set baudrate at 1.826MBps ,see page 986 at reference manual
	/*USARTDIV = Fpclk / (16 * baud_rate)
	     *          = 42000000 / (16 * 1.826MBps) = 1.4375
	     *
	     * DIV_Fraction = 16 * 0.4375 = 0x1
	     * DIV_Mantissa = 1 = 0x1
	     *
	     * BRR          = 0x11 */
	/* Write to USART BRR register */
	USART3->BRR = (uint16_t)0x11;
    	/* Enable USART3 */
	USART3->CR1 |= USART_CR1_UE;
	/* Enable transmitter */
	USART3->CR1 |= USART_CR1_TE;
 }

/**
 * @brief   USART3_char_Transmit to transmit char to the PC over USB.
 * @name    USART3_char_Transmit
 * @param   uint8_t data
 * @retval  UARTTX_STATUS =PASSED OR FAILED
 */
 UARTTX_STATUS USART3_char_Transmit(uint8_t data)
 {
    uint32_t timeout=0;
    // Write data into transmit data register
	USART3->DR = data;
    while((!(USART3->SR & USART_SR_TXE))&& (timeout < UARTTX_TIMEOUT_MAX) )
	{
        timeout++;
	//Wait for transmission buffer empty flag
	}
    if(!(USART3->SR & USART_SR_TXE)){ // If a timeout passed away and USART_SR_TXE had not come up - Error
		return UART_TX_FAILED;
	}
    return UART_TX_PASSED;
 }

/**
 * @brief   USART3_string_Transmit to transmit string to the PC over USB.
 * @name    USART3_string_Transmit
 * @param   uint8_t* msg
 * @retval  UARTTX_STATUS =PASSED OR FAILED
 */
UARTTX_STATUS USART3_string_Transmit(uint8_t*msg)
{
	while (*msg++!='\0')
	{
		if(UART_TX_FAILED==USART3_char_Trans(*msg))
			return UART_TX_FAILED;
	}
	
	return UART_TX_PASSED;
}

/**
 * @brief   USB_transmit_CAN_MSG to transmit CAN_msg along with its id to the PC over USB.
 * @name    USB_transmit_CAN_MSG
 * @param   void
 * @retval  UARTTX_STATUS =PASSED OR FAILED
 */

UARTTX_STATUS USB_transmit_CAN_MSG(void)
{

	USART3_char_Transmit(CAN1_MSG.upper_stdid);
	USART3_char_Transmit(CAN1_MSG.lower_stdid);
	USART3_char_Transmit(' ');
	USART3_char_Transmit(CAN1_MSG.dlc);
	USART3_char_Transmit(' ');
	for(uint8_t cnt=0u ; cnt<CAN1_MSG.dlc;cnt++)
	{
		USART3_char_Transmit(CAN1_MSG.data[cnt]);
		USART3_char_Transmit(' ');
	}
	USART3_char_Transmit('\r');
	USART3_char_Transmit('\n');

}