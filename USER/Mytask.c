/**
  ******************************************************************************
  * @author  Huang.
  * @version V1.0
  * @date    2020-10-18
  * @brief   任务函数C文件
  ******************************************************************************
  * @attention
  *
	*	
  ******************************************************************************
  */
	
#include "Mytask.h"
#include "taskconfig.h"
#include "usart.h"

//Hardware
#include "drv_led.h"
#include "drv_key.h"
#include "drv_oled.h"
#include "drv_RF24L01.h"


void Create_StratTask()
{
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //进入临界区
	
	drv_led_Init();		  			//初始化LED
	drv_key_Init();						//初始化按键
	drv_OLED_Init();					//初始化OLED
	OLED_Clear(); 
	
	drv_spi_init();						//spi初始化
	NRF24L01_GPIO_Init();			//RF24L01引脚初始化
	
	NRF24L01_check( );				//检测nRF24L01
	RF24L01_Init( );
	
	
	//创建OLED任务
	xTaskCreate((TaskFunction_t )OLED_task,     	
							(const char*    )"oled_task",   	
							(uint16_t       )OLED_STK_SIZE, 
							(void*          )NULL,				
							(UBaseType_t    )OLED_TASK_PRIO,	
							(TaskHandle_t*  )&OLEDTask_Handler);   
							
	//创建NRF24L01任务
	xTaskCreate((TaskFunction_t )NRF24L01_task,     
							(const char*    )"nrf24l01_task",   
							(uint16_t       )NRF24L01_STK_SIZE, 
							(void*          )NULL,
							(UBaseType_t    )NRF24L01_TASK_PRIO,
							(TaskHandle_t*  )&NRF24L01Task_Handler); 
								
	//创建LED任务
	xTaskCreate((TaskFunction_t )led_task,     	
						(const char*    )"led_task",   	
						(uint16_t       )LED_STK_SIZE, 
						(void*          )NULL,				
						(UBaseType_t    )LED_TASK_PRIO,	
						(TaskHandle_t*  )&LEDTask_Handler);
						
	//创建按键任务
	xTaskCreate((TaskFunction_t )key_task,     
							(const char*    )"key_task",   
							(uint16_t       )KEY_STK_SIZE, 
							(void*          )NULL,
							(UBaseType_t    )KEY_TASK_PRIO,
							(TaskHandle_t*  )&KEYTask_Handler);
	
//	vTaskSuspend(LED2Task_Handler);//挂起任务led2
							
	vTaskDelete(StartTask_Handler); //删除开始任务
	taskEXIT_CRITICAL();            //退出临界区
}

//提示灯任务函数 
void led_task(void *pvParameters)
{
	for(;;)
	{
		LED0=~LED0;
		vTaskDelay(500);
	}
}   

//OLED任务函数
void OLED_task(void *pvParameters)
{
	for(;;)
	{
	
	}
}

//NRF24L01任务函数
void NRF24L01_task(void *pvParameters)
{
	for(;;)
	{
	
	}
}

//按键任务函数
void key_task(void *pvParameters)
{
	for(;;)
	{
		vTaskDelay(10);
	}
}


