/**
  ******************************************************************************
  * @author  Huang.
  * @version V1.0
  * @date    2020-10-20
  * @brief   任务参数配置H文件
  ******************************************************************************
  * @attention
  *
	*	任务参数配置
  ******************************************************************************
  */
	
	
#ifndef __taskconfig_H__
#define __taskconfig_H__

#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//开始任务
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);


//OLED任务
//任务优先级
#define OLED_TASK_PRIO		3
//任务堆栈大小	
#define OLED_STK_SIZE 		128  
//任务句柄
TaskHandle_t OLEDTask_Handler;
//任务函数
void OLED_task(void *pvParameters);

//NRF24L01任务
//任务优先级
#define NRF24L01_TASK_PRIO		4
//任务堆栈大小	
#define NRF24L01_STK_SIZE 		256  
//任务句柄
TaskHandle_t NRF24L01Task_Handler;
//任务函数
void NRF24L01_task(void *pvParameters);

//led任务
//任务优先级
#define LED_TASK_PRIO		1
//任务堆栈大小	
#define LED_STK_SIZE 		100  
//任务句柄
TaskHandle_t LedTask_Handler;
//任务函数
void led_task(void *pvParameters);

//按键任务
//任务优先级
#define KEY_TASK_PRIO		3
//任务堆栈大小	
#define KEY_STK_SIZE 		128  
//任务句柄
TaskHandle_t KeyTask_Handler;
//任务函数
void key_task(void *pvParameters);

QueueHandle_t   Key_Queue;			//按键队列
QueueHandle_t   Mode_Queue;		//消息队列

#define			KEYMSG_Q_NUM	1
#define			MODE_Q_NUM	1

#endif


