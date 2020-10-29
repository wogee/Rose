/****************************************Copyright (c)****************************************************
**                                     Tomorn  Co.,LTD.
**                                     
**                                   http://www.tomorn.cn
**                                       wujikun
**--------------File Info---------------------------------------------------------------------------------
** File Name:               charger.c
** Last modified Date:      2019.09.18
** Last Version:            1.0
** Description:             
*********************************************************************************************************/
#include <insulation.h>
#include <uart.h> 
#include <calculator.h>
#include <bms.h>

#define INS_ADDR    0x10
#define INS_READ    0x01
#define INS_WRITE   0x02



uint32_t  InsulationResistorOne = 0;		 //��Ե������1
uint32_t  InsulationResistorTwo = 0;		 //��Ե������2
uint32_t  InsuVoltage=0;                 //��Ե��������ѹ

static void InsulationSendFrame(uint8_t ADDR,uint8_t CMD,uint32_t DATA);
static void GetInsulationResistor(void);

void InsulationMain (void)
{   	
  uint8_t i=0;
	
  while (1) 
 {	 

	  OSTimeDlyHMSM(0,0,0,200);	
	 
//��Ե���
	 if(InsulationFlag==1)
	 {		 	
		   InsulationSendFrame(INS_ADDR,INS_WRITE,0x021020);         //������Ե���
					do
					{					
						 i++;						
						 OSTimeDlyHMSM(0,0,1,0);
						 InsulationSendFrame(INS_ADDR,INS_READ,0x02030405);  //��ȡ��Ե�������
						 GetInsulationResistor();				
						 if((InsulationResistorOne>InsuVoltage/10)&&(InsulationResistorTwo>InsuVoltage/10))
						 {
							     InsulationFlag=2;
									 if(PRINT_STRING)
									 {
										 Print("InsuVoltage:%s\n",InsuVoltage);	
										 Print("InsulationResistorOne:%s\n",InsulationResistorOne);	
										 Print("InsulationResistorTwo:%s\n",InsulationResistorTwo);
									 }								 
						 }			 
					}while(i<20);	
				 i=0;	
				 InsulationSendFrame(INS_ADDR,INS_WRITE,0x021000);	      //�رվ�Ե���		
				 InsulationFlag=2;	
	 }
	 
//����ⲿ��ѹ����10V	 
	 if(OutVoltageDetFlag==1)
	   {
	        InsulationSendFrame(INS_ADDR,INS_READ,0x02030405);     //��ȡ��ѹ�������
					 do
					{		
						 i++;				
						 OSTimeDlyHMSM(0,0,1,0);
						 GetInsulationResistor();
//						 if(((InsuVoltage-BMSMessage.BatteryVoltage)<(InsuVoltage/20))||((BMSMessage.BatteryVoltage-InsuVoltage)<(InsuVoltage/20)))
//						 {
//							OutVoltageDetFlag=2;
//							if(PRINT_STRING)
//							 {
//								Print("InsuVoltage:%s\n",InsuVoltage); 
//							 }
//							}
//						 else
//							OutVoltageDetFlag=3;
						}while(i<3);	
//ǿ�Ƹ�ֵ��ʹ����ⲿ��ѹͨ��					
//					if(i>=3)
//					{
//						 i=0;	
						 OutVoltageDetFlag=2;	
//					}						
	    }	  			 
   }
}
 
static void InsulationSendFrame(uint8_t ADDR,uint8_t CMD,uint32_t DATA)
{
	   uint8_t data[8];
	   uint8_t *pdat;
	   pdat = data;
		*pdat++ = ADDR;
		*pdat++ = CMD;
		*pdat++ = (DATA>>24)&0xff;
		*pdat++ = (DATA>>16)&0xff;	
		*pdat++ = (DATA>>8)&0xff;
		*pdat++ =  DATA&0xff;		   
		*pdat++ =  MODBUS_CRC(data,6)&0xff;
		*pdat++ =  (MODBUS_CRC(data,6)>>8)&0xff;
    UART1SendStr(data,sizeof(data));
	
}

void GetInsulationResistor(void)
{
		if((RcvBufU1[0]==0x10)&&((RcvBufU1[1]&0x10)==0x10))
		{
				InsuVoltage = (RcvBufU1[2]<<8) + RcvBufU1[3];
				InsulationResistorOne = (RcvBufU1[4]<<8) + RcvBufU1[5];
				InsulationResistorTwo = (RcvBufU1[6]<<8) + RcvBufU1[7];

		}
		UART1RxbufClear();
}
