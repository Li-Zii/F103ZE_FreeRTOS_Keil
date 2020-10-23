/**
  ******************************************************************************
  * @author  Huang.
  * @version V3.0
  * @date    2020-10-18
  * @brief   ��������C�ļ�
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


#include "drv_key.h"
#include "delay.h"

/*******************************************************************************
* �� �� ��         : drv_key_Init
* ��������		   : ������ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void drv_key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����ṹ�����	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=KEY_UP_Pin;	   //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//��������  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //���ô�������
	GPIO_Init(KEY_UP_Port,&GPIO_InitStructure);		  /* ��ʼ��GPIO */
	
	GPIO_InitStructure.GPIO_Pin=KEY_0_Pin|KEY_1_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_Port,&GPIO_InitStructure);
}

/*******************************************************************************
* �� �� ��         : KEY_Scan
* ��������		   : ����ɨ����
* ��    ��         : mode=0:���ΰ��°���
					 mode=1���������°���
* ��    ��         : 0��δ�а�������
					 KEY_UP��K_UP������
					 KEY_0��K_0������
					 KEY_1��K_1������
*******************************************************************************/
u8 KEY_Scan(u8 mode)
{
	static u8 key=1;
	if(key==1&&(K_UP==1||K_0==0||K_1==0)) //����һ����������
	{
		delay_xms(10);  //����
		key=0;
		if(K_UP==1)
		{
			return KEY_UP; 
		}
		else if(K_0==0)
		{
			return KEY_0; 
		}
		else if(K_1==0)
		{
			return KEY_1; 
		}
		
	}
	else if(K_UP==0&&K_0==1&&K_1==1)    //�ް�������
	{
		key=1;
	}
	if(mode==1) //������������
	{
		key=1;
	}
	return 0;
}

