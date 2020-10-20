/**
  ******************************************************************************
  * @author  Huang.
  * @version V1.0
  * @date    2020-10-18
  * @brief   ������C�ļ�
  ******************************************************************************
  * @attention
  *
	*	
  ******************************************************************************
  */


//System
#include "main.h"				//main.h �к���TX/RX�����SPI/Ӳ��SPIѡ������ѡ��
#include "sys.h"
#include "delay.h"
#include "usart.h"

//Hardware
//#include "drv_led.h"
//#include "drv_key.h"
//#include "drv_oled.h"
//#include "drv_RF24L01.h"

//FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "Mytask.h"


/**
  * @brief :������ 
  * @param :��
  * @note  :��
  * @retval:��
  */ 
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 ȫ��������ռ
	delay_init();	    				//��ʱ������ʼ��	  
	uart_init(115200);				//��ʼ������
						
	Create_StratTask();				//��ʼ�����ʼ��
}


