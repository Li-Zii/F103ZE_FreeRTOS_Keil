/**
  ******************************************************************************
  * @author  Huang.
  * @version V1.0
  * @date    2020-10-20
  * @brief   �����������H�ļ�
  ******************************************************************************
  * @attention
  *
	*	�����������
  ******************************************************************************
  */
	
	
#ifndef __taskconfig_H__
#define __taskconfig_H__

#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"

//��ʼ����
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);


//OLED����
//�������ȼ�
#define OLED_TASK_PRIO		3
//�����ջ��С	
#define OLED_STK_SIZE 		100  
//������
TaskHandle_t OLEDTask_Handler;
//������
void OLED_task(void *pvParameters);

//NRF24L01����
//�������ȼ�
#define NRF24L01_TASK_PRIO		4
//�����ջ��С	
#define NRF24L01_STK_SIZE 		100  
//������
TaskHandle_t NRF24L01Task_Handler;
//������
void NRF24L01_task(void *pvParameters);

//led����
//�������ȼ�
#define LED_TASK_PRIO		1
//�����ջ��С	
#define LED_STK_SIZE 		100  
//������
TaskHandle_t LEDTask_Handler;
//������
void led_task(void *pvParameters);

//��������
//�������ȼ�
#define KEY_TASK_PRIO		2
//�����ջ��С	
#define KEY_STK_SIZE 		128  
//������
TaskHandle_t KEYTask_Handler;
//������
void key_task(void *pvParameters);

#endif


