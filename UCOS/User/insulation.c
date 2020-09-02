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

uint8_t InsulationFlag    = 0;
uint8_t OutVoltageDetFlag = 0;

uint32_t  InsulationResistorOne = 0;		 //¾øÔµ¼ì²âµç×è1
uint32_t  InsulationResistorTwo = 0;		 //¾øÔµ¼ì²âµç×è2
uint32_t  InsuVoltage=0;                 //¾øÔµ¼ì²â²âÁ¿µçÑ¹

static void InsulationSendFrame(uint8_t ADDR,uint8_t CMD,uint32_t DATA);
static void GetInsulationResistor(void);

void InsulationMain (void)
{   	
	
  while (1) 
 {	 
	   uint8_t i=0;
	  OSTimeDlyHMSM(0,0,0,500);	
	 if(InsulationFlag==1)
	 {		 	
		   InsulationSendFrame(INS_ADDR,INS_WRITE,0x021020);         //¿ªÆô¾øÔµ¼ì²â
					do
					{					
						 i++;						
						 OSTimeDlyHMSM(0,0,1,0);
						 InsulationSendFrame(INS_ADDR,INS_READ,0x02030405);  //¶ÁÈ¡¾øÔµ¼ì²âÊý¾Ý
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
				 InsulationSendFrame(INS_ADDR,INS_WRITE,0x021000);	      //¹Ø±Õ¾øÔµ¼ì²â		
				 InsulationFlag=2;	
	 }
	 if(OutVoltageDetFlag==1)
	   {
	        InsulationSendFrame(INS_ADDR,INS_READ,0x02030405);     //¶ÁÈ¡¾øÔµ¼ì²âÊý¾Ý
					 do
					{		
						 i++;				
						 OSTimeDlyHMSM(0,0,1,0);
						 GetInsulationResistor();
						 if(((InsuVoltage-BMSMessage.BatteryVoltage)<(InsuVoltage/20))||((BMSMessage.BatteryVoltage-InsuVoltage)<(InsuVoltage/20)))
						 {
							OutVoltageDetFlag=2;
							if(PRINT_STRING)
							 {
								Print("InsuVoltage:%s\n",InsuVoltage); 
							 }
							}
//						 else
//							OutVoltageDetFlag=3;
						}while(i<3);	
         	 i=0;	
           OutVoltageDetFlag=2;						
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
