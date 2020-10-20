/**
  ******************************************************************************
  * @author  Huang.
  * @version V3.0
  * @date    2020-10-18
  * @brief   SPI����H�ļ�
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__


#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "main.h"



//SPI���Ŷ���
#define SPI_CLK_GPIO_PORT			GPIOB
#define SPI_CLK_GPIO_CLK			RCC_APB2Periph_GPIOB
#define SPI_CLK_GPIO_PIN			GPIO_Pin_13

#define SPI_MISO_GPIO_PORT			GPIOB
#define SPI_MISO_GPIO_CLK			RCC_APB2Periph_GPIOB
#define SPI_MISO_GPIO_PIN			GPIO_Pin_14

#define SPI_MOSI_GPIO_PORT			GPIOB
#define SPI_MOSI_GPIO_CLK			RCC_APB2Periph_GPIOB
#define SPI_MOSI_GPIO_PIN			GPIO_Pin_15

#define SPI_NSS_GPIO_PORT			GPIOG
#define SPI_NSS_GPIO_CLK			RCC_APB2Periph_GPIOG
#define SPI_NSS_GPIO_PIN			GPIO_Pin_7


#define spi_set_nss_high( )			SPI_NSS_GPIO_PORT->ODR |= SPI_NSS_GPIO_PIN								//Ƭѡ�ø�
#define spi_set_nss_low( )			SPI_NSS_GPIO_PORT->ODR &= (uint32_t)( ~((uint32_t)SPI_NSS_GPIO_PIN ))	//Ƭѡ�õ�



#ifdef __USE_SOFT_SPI_INTERFACE__			/** ֻ��ʹ�����SPI����Ҫ�ķ�װ */			

#define spi_set_clk_high( )			SPI_CLK_GPIO_PORT->ODR |= SPI_CLK_GPIO_PIN								//ʱ���ø�
#define spi_set_clk_low( )			SPI_CLK_GPIO_PORT->ODR &= (uint32_t)( ~((uint32_t)SPI_CLK_GPIO_PIN ))	//ʱ���õ�

#define spi_set_mosi_hight( )		SPI_MOSI_GPIO_PORT->ODR |= SPI_MOSI_GPIO_PIN							//���ͽ��ø�
#define spi_set_mosi_low( )			SPI_MOSI_GPIO_PORT->ODR &= (uint32_t)( ~((uint32_t)SPI_MOSI_GPIO_PIN ))	//���ͽ��õ�

#define spi_get_miso( )				(( SPI_MISO_GPIO_PORT->IDR & (uint32_t)SPI_MISO_GPIO_PIN) != SPI_MISO_GPIO_PIN ) ? 0 : 1 // ����Ӧ����λΪ����õ�0����Ӧ����λΪ����õ�1


void drv_spi_init( void );
uint8_t drv_spi_read_write_byte( uint8_t TxByte );
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );


#else									/** ֻ��ʹ��Ӳ��SPIʱ��ʹ�� */


//SPI�ӿڶ���
#define SPI_PORT					SPI2						//SPI�ӿ�
#define SPI_PORT_CLK				RCC_APB1Periph_SPI2			//SPIʱ��


void drv_spi_init( void );
uint8_t drv_spi_read_write_byte( uint8_t TxByte );
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );

#endif



#endif

