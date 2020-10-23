/**
  ******************************************************************************
  * @author  Huang.
  * @version V1.0
  * @date    2020-10-18
  * @brief   主函数C文件
  ******************************************************************************
  * @attention
  *
	*	
  ******************************************************************************
  */


//System
#include "main.h"				//main.h 中含有TX/RX、软件SPI/硬件SPI选择配置选项
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
  * @brief :主函数 
  * @param :无
  * @note  :无
  * @retval:无
  */ 
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 全部用于抢占
	delay_init();	    				//延时函数初始化	  
	uart_init(115200);				//初始化串口
	
	Create_StratTask();				//开始任务初始化
}


