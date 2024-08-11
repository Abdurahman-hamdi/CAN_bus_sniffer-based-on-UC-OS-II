/**
  ******************************************************************************
  * @file    GPIO.c
  * @author Abdulrahman Hami
  * @version v0.1
  * @date    12-Aug-2024
  * @brief   This file contains all the functions implementation to be used to init GPIO drivers for CAN and UART.
  ******************************************************************************/

 /****************************************** Includes***************************/
 #include"GPIO.h"

/******************************************* Constants ************************/

#define GPIO_AFRH_AFRH11                     ((uint32_t) 0x0000F000)
#define GPIO_AFRH_AFRH11_AF9                ((uint32_t) 0x00009000)
#define GPIO_AFRH_AFRH12                     ((uint32_t) 0x000F0000)
#define GPIO_AFRH_AFRH12_AF9                 ((uint32_t) 0x00090000)
 /**************************************functions implementation****************/

 /**
 * @brief   CAN1_GPIO init which configures PA11(CAN1_RX) and PA12 (CAN1_TX)
 * @name    CAN1_GPIO_config
 * @param   none
 * @retval  none
 */
void CAN1_GPIO_config(void)
{
    /* Enable port A clock */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  /* Select alternate function mode */
  GPIOA->MODER &= ~(GPIO_MODER_MODER11 | GPIO_MODER_MODER12);
  GPIOA->MODER |= (GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1);

  /* Select output type push-pull */
  GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_12);

  /* Select output speed medium */
  GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR12);
  GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR12_0);

  /* Select pull up */
  GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR11 | GPIO_PUPDR_PUPDR12);
  GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR11_0 | GPIO_PUPDR_PUPDR12_0);
  /* Select AF9 */
  GPIOA->AFR[1] &= ~(GPIO_AFRH_AFRH11 | GPIO_AFRH_AFRH12);
  GPIOA->AFR[1] |= (GPIO_AFRH_AFRH11_AF9 | GPIO_AFRH_AFRH12_AF9);
}


 /**
 * @brief   USART3_GPIO init whic configure Tx(Pb10)and Rx(Pb11)
 * @name    USART3_GPIO_Config
 * @param   none
 * @retval  none
 */
void USART3_GPIO_Config(void)
{

  /* Enable port b clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    /* Select alternate function mode */
    GPIOB->MODER &= ~(GPIO_MODER_MODER10 | GPIO_MODER_MODER11);
    GPIOB->MODER |= (GPIO_MODER_MODER10_1 | GPIO_MODER_MODER11_1);

    /* Select output type push-pull for Tx(Pb10) */
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_10);

    /* Select output speed medium for Tx(Pb10) */
    GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR10);
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_0;

    /* Select pull up */
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR10 | GPIO_PUPDR_PUPDR11);
    GPIOB->PUPDR |= (GPIO_PUPDR_PUPDR10_0 | GPIO_PUPDR_PUPDR11_0);

    //alternative function for portb, pins 10 and 11
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
}