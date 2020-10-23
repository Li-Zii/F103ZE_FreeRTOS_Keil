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

extern u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u16 USART_RX_STA;       //����״̬���	  


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
	OLED_ShowString(6,3,"static send",16);
	
	drv_spi_init();						//spi��ʼ��
	NRF24L01_GPIO_Init();			//RF24L01���ų�ʼ��
	
	NRF24L01_check( );				//���nRF24L01
	RF24L01_Init( );
	
	//��������
	Key_Queue=xQueueCreate(KEYMSG_Q_NUM,sizeof(u8));
	Mode_Queue=xQueueCreate(MODE_Q_NUM,sizeof(u8));
	
	if(Key_Queue == NULL)
	{
		//printf("Create Queue Failed!\r\n");
	}
	
		//������������
	xTaskCreate((TaskFunction_t )key_task,     
							(const char*    )"key_task",   
							(uint16_t       )KEY_STK_SIZE, 
							(void*          )NULL,
							(UBaseType_t    )KEY_TASK_PRIO,
							(TaskHandle_t*  )&KeyTask_Handler);
							
	//����NRF24L01����
	xTaskCreate((TaskFunction_t )NRF24L01_task,     
							(const char*    )"nrf24l01_task",   
							(uint16_t       )NRF24L01_STK_SIZE, 
							(void*          )NULL,
							(UBaseType_t    )NRF24L01_TASK_PRIO,
							(TaskHandle_t*  )&NRF24L01Task_Handler); 
	
	//����OLED����
	xTaskCreate((TaskFunction_t )OLED_task,     	
							(const char*    )"oled_task",   	
							(uint16_t       )OLED_STK_SIZE, 
							(void*          )NULL,				
							(UBaseType_t    )OLED_TASK_PRIO,	
							(TaskHandle_t*  )&OLEDTask_Handler);   
								
	//����LED����
	xTaskCreate((TaskFunction_t )led_task,     	
						(const char*    )"led_task",   	
						(uint16_t       )LED_STK_SIZE, 
						(void*          )NULL,				
						(UBaseType_t    )LED_TASK_PRIO,	
						(TaskHandle_t*  )&LedTask_Handler);
						

	
//	vTaskSuspend(LED2Task_Handler);//��������led2
							
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
						
	taskEXIT_CRITICAL();            //�˳��ٽ���
}

//����������
void key_task(void *pvParameters)
{
	u8 BUTOTN_PRESS_DOWN;
	BaseType_t error;
	
	while(1)
	{
		BUTOTN_PRESS_DOWN = KEY_Scan(0);
//		BUTOTN_PRESS_DOWN = 2;
		if( (Key_Queue != NULL) && (BUTOTN_PRESS_DOWN) )		//������Ч�����Ұ�����Ч
		{
			error=xQueueOverwrite(Key_Queue,&BUTOTN_PRESS_DOWN);		//��д��ʽ���
			if(error != pdTRUE)
			{
				taskENTER_CRITICAL();           //�����ٽ���
				
				printf("Key_Queue Send Failed!\r\n");
				
				taskEXIT_CRITICAL();            //�˳��ٽ���
			}
		}
		vTaskDelay(10);
	}
}

//NRF24L01������
void NRF24L01_task(void *pvParameters)
{
	u8 i = 0;
	u8 g_TxMode = 0;
	u8 BUTOTN_PRESS_DOWN = 0;
//	u8 g_UartRxBuffer[ 100 ] = { 0 };
	
	const char *g_Ashining = "Li_Zii";
	
	BaseType_t error;
	BaseType_t M_error;
	
	while(1)
	{
		if(Key_Queue!=NULL)
		{
			error=xQueueReceive(Key_Queue,&BUTOTN_PRESS_DOWN,0);		//���Ӳ��ȴ�
			if(error==pdTRUE) //��ȡ��Ϣ�ɹ�
			{
				taskENTER_CRITICAL();           //�����ٽ���
				
				printf("Kqueue is ok! value is %d\r\n",BUTOTN_PRESS_DOWN);
				
				taskEXIT_CRITICAL();            //�˳��ٽ���
				
				if( BUTOTN_PRESS_DOWN == 2 )		//����0��Ч
				{
					g_TxMode = 1 - g_TxMode;		//ģʽ���� TX_MODE_1( 0 ),TX_MODE_2( 1 )֮���л�
					if( Mode_Queue != NULL )		//������Ч
					{
						M_error=xQueueOverwrite(Mode_Queue,&g_TxMode);		//��д��ʽ���
						if(M_error != pdTRUE)
						{
							taskENTER_CRITICAL();           //�����ٽ���
							
							printf("Mode_Queue Send Failed!\r\n");
							
							taskEXIT_CRITICAL();            //�˳��ٽ���
						}
					}
				}
			}	
			//����
			if( TX_MODE_1 == g_TxMode )
			{
				NRF24L01_TxPacket( (uint8_t *)g_Ashining, 6 );		//ģʽ1���͹̶��ַ�,1Sһ��	
				LED1=~LED1;
			}
			else
			{	
				//��ѯ��������
				i = USART_RX_STA;
					
				if( 0 != i )
				{
					NRF24L01_TxPacket( USART_RX_BUF, i );
					LED1=~LED1;
				}
			}
			vTaskDelay(1000); 
		}
		else
		{
			vTaskDelay(1000); 
		}
	}
}

//OLED������
void OLED_task(void *pvParameters)
{
	u8 g_TxMode;
	
	BaseType_t M_error;
	
	while(1)
	{
//		printf("OLED running\r\n");
		if(Mode_Queue!=NULL)
		{
			M_error=xQueueReceive(Mode_Queue,&g_TxMode,0);		//���Ӳ��ȴ�
			if(M_error==pdTRUE) //��ȡ��Ϣ�ɹ�
			{
				taskENTER_CRITICAL();           //�����ٽ���
				
				printf("Mqueue is ok! value is %d\r\n",g_TxMode);
				
				taskEXIT_CRITICAL();            //�˳��ٽ���
				if( g_TxMode == 0 )
				{
					OLED_Clear();
					OLED_ShowString(6,3,"static send",16);
				}
				else
				{
						OLED_Clear();
						OLED_ShowString(6,3,"usart send",16);
				}
			}
		}
		vTaskDelay(500);
	}
}

//��ʾ�������� 
void led_task(void *pvParameters)
{
	while(1)
	{
		LED0=~LED0;
		vTaskDelay(200);
	}
}   








