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
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //�����ٽ���
	
	drv_led_Init();		  			//��ʼ��LED
	drv_key_Init();						//��ʼ������
	drv_OLED_Init();					//��ʼ��OLED
	OLED_Clear(); 
	
	drv_spi_init();						//spi��ʼ��
	NRF24L01_GPIO_Init();			//RF24L01���ų�ʼ��
	
	NRF24L01_check( );				//���nRF24L01
	RF24L01_Init( );
	
	
	//����OLED����
	xTaskCreate((TaskFunction_t )OLED_task,     	
							(const char*    )"oled_task",   	
							(uint16_t       )OLED_STK_SIZE, 
							(void*          )NULL,				
							(UBaseType_t    )OLED_TASK_PRIO,	
							(TaskHandle_t*  )&OLEDTask_Handler);   
							
	//����NRF24L01����
	xTaskCreate((TaskFunction_t )NRF24L01_task,     
							(const char*    )"nrf24l01_task",   
							(uint16_t       )NRF24L01_STK_SIZE, 
							(void*          )NULL,
							(UBaseType_t    )NRF24L01_TASK_PRIO,
							(TaskHandle_t*  )&NRF24L01Task_Handler); 
								
	//����LED����
	xTaskCreate((TaskFunction_t )led_task,     	
						(const char*    )"led_task",   	
						(uint16_t       )LED_STK_SIZE, 
						(void*          )NULL,				
						(UBaseType_t    )LED_TASK_PRIO,	
						(TaskHandle_t*  )&LEDTask_Handler);
						
	//������������
	xTaskCreate((TaskFunction_t )key_task,     
							(const char*    )"key_task",   
							(uint16_t       )KEY_STK_SIZE, 
							(void*          )NULL,
							(UBaseType_t    )KEY_TASK_PRIO,
							(TaskHandle_t*  )&KEYTask_Handler);
	
//	vTaskSuspend(LED2Task_Handler);//��������led2
							
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
	taskEXIT_CRITICAL();            //�˳��ٽ���
}

//��ʾ�������� 
void led_task(void *pvParameters)
{
	for(;;)
	{
		LED0=~LED0;
		vTaskDelay(500);
	}
}   

//OLED������
void OLED_task(void *pvParameters)
{
	for(;;)
	{
	
	}
}

//NRF24L01������
void NRF24L01_task(void *pvParameters)
{
	for(;;)
	{
	
	}
}

//����������
void key_task(void *pvParameters)
{
	for(;;)
	{
		vTaskDelay(10);
	}
}


