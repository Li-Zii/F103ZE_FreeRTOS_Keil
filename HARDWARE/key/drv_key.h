/**
  ******************************************************************************
  * @author  Huang.
  * @version V3.0
  * @date    2020-10-18
  * @brief   按键配置H文件
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */



#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__



#include "sys.h"
 
#define KEY_ONE_Pin     GPIO_Pin_3    //定义K_DOWN管脚
#define KEY_TWO_Pin   	GPIO_Pin_4   //定义K_RIGHT管脚
#define KEY_UP_Pin      GPIO_Pin_0  //定义KEY_UP管脚

#define KEY_Port (GPIOE) //定义端口
#define KEY_UP_Port (GPIOA) //定义端口


//使用位操作定义
#define K_UP PAin(0)
#define K_ONE PEin(3)
#define K_TWO PEin(4)

//使用读取管脚状态库函数定义 
//#define K_UP      GPIO_ReadInputDataBit(KEY_UP_Port,KEY_UP_Pin)
//#define K_DOWN    GPIO_ReadInputDataBit(KEY_Port,KEY_DOWN_Pin)
//#define K_LEFT    GPIO_ReadInputDataBit(KEY_Port,KEY_LEFT_Pin)
//#define K_RIGHT   GPIO_ReadInputDataBit(KEY_Port,KEY_RIGHT_Pin)


//定义各个按键值  
#define KEY_UP 1
#define KEY_ONE 2
#define KEY_TWO 3
 



void drv_key_Init(void);
u8 KEY_Scan(u8 mode);
#endif
