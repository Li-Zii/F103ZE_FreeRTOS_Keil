/**
  ******************************************************************************
  * @author  Huang.
  * @version V3.0
  * @date    2020-10-18
  * @brief   ��������H�ļ�
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */



#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__



#include "sys.h"
 
#define KEY_ONE_Pin     GPIO_Pin_3    //����K_DOWN�ܽ�
#define KEY_TWO_Pin   	GPIO_Pin_4   //����K_RIGHT�ܽ�
#define KEY_UP_Pin      GPIO_Pin_0  //����KEY_UP�ܽ�

#define KEY_Port (GPIOE) //����˿�
#define KEY_UP_Port (GPIOA) //����˿�


//ʹ��λ��������
#define K_UP PAin(0)
#define K_ONE PEin(3)
#define K_TWO PEin(4)

//ʹ�ö�ȡ�ܽ�״̬�⺯������ 
//#define K_UP      GPIO_ReadInputDataBit(KEY_UP_Port,KEY_UP_Pin)
//#define K_DOWN    GPIO_ReadInputDataBit(KEY_Port,KEY_DOWN_Pin)
//#define K_LEFT    GPIO_ReadInputDataBit(KEY_Port,KEY_LEFT_Pin)
//#define K_RIGHT   GPIO_ReadInputDataBit(KEY_Port,KEY_RIGHT_Pin)


//�����������ֵ  
#define KEY_UP 1
#define KEY_ONE 2
#define KEY_TWO 3
 



void drv_key_Init(void);
u8 KEY_Scan(u8 mode);
#endif