/**
  ******************************************************************************
  * @author  Huang.
  * @version V3.0
  * @date    2020-10-18
  * @brief   UART配置H文件
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __USART_H__
#define __USART_H__


#include "stdio.h"	
#include "sys.h" 


#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	


//串口硬件定义
#define UART_PORT					USART1
#define UART_PORT_CLK				RCC_APB2Periph_USART1
#define UART_PORT_AF				GPIO_Remap_USART1

//串口引脚定义
#define UART_TX_GPIO_PORT			GPIOA
#define UART_TX_GPIO_CLK			RCC_APB2Periph_GPIOA
#define UART_TX_GPIO_PIN			GPIO_Pin_9

#define UART_RX_GPIO_PORT			GPIOA
#define UART_RX_GPIO_CLK			RCC_APB2Periph_GPIOA
#define UART_RX_GPIO_PIN			GPIO_Pin_10


void drv_uart_init( uint32_t UartBaudRate );
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length );
uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer );


//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length );
uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer );


#endif


