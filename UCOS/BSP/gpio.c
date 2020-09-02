/****************************************Copyright (c)****************************************************
**                                     Tomorn  Co.,LTD.
**                                     
**                                 http://www.tomorn.cn
**                                       wujikun
**--------------File Info---------------------------------------------------------------------------------
** File Name:               GPIO.c
** Last modified Date:      2017.05.18
** Last Version:            1.0
** Description:             
*********************************************************************************************************/
#include <gpio.h>

void GPIOInit(void )
{	     	
  SYSLED_OFF();
	FRAM_CS_H();
	CHARGERNO_INT_Init();
  STOP_INT_Init(); 	
  DOOR_INT_Init();
	LOCK_INT_Init();
	TEMPswitch_INT_Init();
  DCswitch_INT_Init();
	INswitch_INT_Init();	
	
}
