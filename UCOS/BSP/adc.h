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


#define ADC_CHN				  4		    /*	ת����ͨ��	  */
#define ADC_TIMES				100	  	/*	��������	  */


#define 	CNT_ETH	 0x000				 			//���˿ڽӵ�
#define 	CNT_WRK	 0x3e0				 			//���˿ڲ�ǹ
#define 	CNT_CON	 0x5d2	 						//���˿����ӳ��ǹ
#define 	CNT_OPN	 0xba2	 						//���˿�����,��Ӧ��ֵ�����
#define 	MIN4V	 	(CNT_WRK-0xc8)			//�������CC��ѹ��Сֵ
#define 	MAX4V	 	(CNT_WRK+0xc8)			//�������CC��ѹ���ֵ
#define 	MIN6V	 	(CNT_CON-0xc8)	 		//���˿����ӣ�������S2δ�ر�,��Ӧ��ѹֵ2740ŷ��
#define 	MAX6V	 	(CNT_CON+0xc8)	 		//���˿����ӣ�������S2δ�ر�,��Ӧ��ѹֵ2740ŷ��
#define 	MIN12V	(CNT_CON+0xc8)			//���˿�����,��Ӧ��ֵ�����
#define 	MAX12V	(CNT_OPN+0xc8)			//���˿�����,��Ӧ��ֵ�����

#define 	ADC0V					1
#define		ADC4V					2
#define		ADC6V					3
#define		ADC12V				4

extern uint32_t ADstatus;
extern void ADCInit( uint32_t ADC_Clk );
extern void ADCScan(void);
extern void ADCMain(void);





























#endif
