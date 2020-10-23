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

extern u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern u16 USART_RX_STA;       //接收状态标记	  


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
	OLED_ShowString(6,3,"static send",16);
	
	drv_spi_init();						//spi初始化
	NRF24L01_GPIO_Init();			//RF24L01引脚初始化
	
	NRF24L01_check( );				//检测nRF24L01
	RF24L01_Init( );
	
	//创建队列
	Key_Queue=xQueueCreate(KEYMSG_Q_NUM,sizeof(u8));
	Mode_Queue=xQueueCreate(MODE_Q_NUM,sizeof(u8));
	
	if(Key_Queue == NULL)
	{
		//printf("Create Queue Failed!\r\n");
	}
	
		//创建按键任务
	xTaskCreate((TaskFunction_t )key_task,     
							(const char*    )"key_task",   
							(uint16_t       )KEY_STK_SIZE, 
							(void*          )NULL,
							(UBaseType_t    )KEY_TASK_PRIO,
							(TaskHandle_t*  )&KeyTask_Handler);
							
	//创建NRF24L01任务
	xTaskCreate((TaskFunction_t )NRF24L01_task,     
							(const char*    )"nrf24l01_task",   
							(uint16_t       )NRF24L01_STK_SIZE, 
							(void*          )NULL,
							(UBaseType_t    )NRF24L01_TASK_PRIO,
							(TaskHandle_t*  )&NRF24L01Task_Handler); 
	
	//创建OLED任务
	xTaskCreate((TaskFunction_t )OLED_task,     	
							(const char*    )"oled_task",   	
							(uint16_t       )OLED_STK_SIZE, 
							(void*          )NULL,				
							(UBaseType_t    )OLED_TASK_PRIO,	
							(TaskHandle_t*  )&OLEDTask_Handler);   
								
	//创建LED任务
	xTaskCreate((TaskFunction_t )led_task,     	
						(const char*    )"led_task",   	
						(uint16_t       )LED_STK_SIZE, 
						(void*          )NULL,				
						(UBaseType_t    )LED_TASK_PRIO,	
						(TaskHandle_t*  )&LedTask_Handler);
						

	
//	vTaskSuspend(LED2Task_Handler);//挂起任务led2
							
	vTaskDelete(StartTask_Handler); //删除开始任务
						
	taskEXIT_CRITICAL();            //退出临界区
}

//按键任务函数
void key_task(void *pvParameters)
{
	u8 BUTOTN_PRESS_DOWN;
	BaseType_t error;
	
	while(1)
	{
		BUTOTN_PRESS_DOWN = KEY_Scan(0);
//		BUTOTN_PRESS_DOWN = 2;
		if( (Key_Queue != NULL) && (BUTOTN_PRESS_DOWN) )		//队列有效，并且按键有效
		{
			error=xQueueOverwrite(Key_Queue,&BUTOTN_PRESS_DOWN);		//覆写方式入队
			if(error != pdTRUE)
			{
				taskENTER_CRITICAL();           //进入临界区
				
				printf("Key_Queue Send Failed!\r\n");
				
				taskEXIT_CRITICAL();            //退出临界区
			}
		}
		vTaskDelay(10);
	}
}

//NRF24L01任务函数
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
			error=xQueueReceive(Key_Queue,&BUTOTN_PRESS_DOWN,0);		//出队不等待
			if(error==pdTRUE) //获取消息成功
			{
				taskENTER_CRITICAL();           //进入临界区
				
				printf("Kqueue is ok! value is %d\r\n",BUTOTN_PRESS_DOWN);
				
				taskEXIT_CRITICAL();            //退出临界区
				
				if( BUTOTN_PRESS_DOWN == 2 )		//按键0有效
				{
					g_TxMode = 1 - g_TxMode;		//模式会在 TX_MODE_1( 0 ),TX_MODE_2( 1 )之间切换
					if( Mode_Queue != NULL )		//队列有效
					{
						M_error=xQueueOverwrite(Mode_Queue,&g_TxMode);		//覆写方式入队
						if(M_error != pdTRUE)
						{
							taskENTER_CRITICAL();           //进入临界区
							
							printf("Mode_Queue Send Failed!\r\n");
							
							taskEXIT_CRITICAL();            //退出临界区
						}
					}
				}
			}	
			//发送
			if( TX_MODE_1 == g_TxMode )
			{
				NRF24L01_TxPacket( (uint8_t *)g_Ashining, 6 );		//模式1发送固定字符,1S一包	
				LED1=~LED1;
			}
			else
			{	
				//查询串口数据
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

//OLED任务函数
void OLED_task(void *pvParameters)
{
	u8 g_TxMode;
	
	BaseType_t M_error;
	
	while(1)
	{
//		printf("OLED running\r\n");
		if(Mode_Queue!=NULL)
		{
			M_error=xQueueReceive(Mode_Queue,&g_TxMode,0);		//出队不等待
			if(M_error==pdTRUE) //获取消息成功
			{
				taskENTER_CRITICAL();           //进入临界区
				
				printf("Mqueue is ok! value is %d\r\n",g_TxMode);
				
				taskEXIT_CRITICAL();            //退出临界区
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

//提示灯任务函数 
void led_task(void *pvParameters)
{
	while(1)
	{
		LED0=~LED0;
		vTaskDelay(200);
	}
}   








