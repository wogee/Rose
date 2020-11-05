#ifndef __ADC_H_
#define __ADC_H_
#include "LPC177x_8x.h"
#include "lpc_types.h"
#include "system_LPC177x_8x.h"
#include <ucos_ii.h>

#define ADC_12BITS          1

#define ADC_DONE            0x80000000
#define ADC_OVERRUN         0x40000000
#define ADC_ADINT           0x00010000

#define ADC_NUM             10


#define ADC_CHN				  4		    /*	转换用通道	  */
#define ADC_TIMES				100	  	/*	采样次数	  */


#define 	CNT_ETH	 0x000				 			//充电端口接地
#define 	CNT_WRK	 0x3e0				 			//检测端口插枪
#define 	CNT_CON	 0x5d2	 						//充电端口连接充电枪
#define 	CNT_OPN	 0xba2	 						//充电端口悬空,对应阻值无穷大
#define 	MIN4V	 	(CNT_WRK-0xc8)			//开启充电CC电压最小值
#define 	MAX4V	 	(CNT_WRK+0xc8)			//开启充电CC电压最大值
#define 	MIN6V	 	(CNT_CON-0xc8)	 		//检测端口连接（汽车端S2未关闭,对应分压值2740欧）
#define 	MAX6V	 	(CNT_CON+0xc8)	 		//检测端口连接（汽车端S2未关闭,对应分压值2740欧）
#define 	MIN12V	(CNT_CON+0xc8)			//检测端口悬空,对应阻值无穷大
#define 	MAX12V	(CNT_OPN+0xc8)			//检测端口悬空,对应阻值无穷大

#define 	ADC0V					1
#define		ADC4V					2
#define		ADC6V					3
#define		ADC12V				4

extern uint32_t ADstatus;
extern void ADCInit( uint32_t ADC_Clk );
extern void ADCScan(void);
extern void ADCMain(void);





























#endif
