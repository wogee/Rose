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
#include <module.h>
#include <insulation.h>
#include <adc.h>

static void	Module_RECData_Pro(void);  
static void ModuleSet(uint8_t CMD, uint16_t V, uint16_t I,uint8_t ModuleType);
static void ModuleGet(uint8_t CMD,uint32_t Voltage,uint32_t Current,uint8_t err);

static void AnalyseMT30(void);
static void AnalyseMT31(void);
static void AnalyseMT32(void);
static void AnalyseMT33(void);
static void AnalyseMT34(void);
static void AnalyseMT35(void);
static void AnalyseMT36(void);
static void AnalyseMT37(void);

static void InitiateMT30(void);
static void InitiateMT31(void);
static void InitiateMT32(void);
static void InitiateMT33(void);
static void InitiateMT34(void);
static void InitiateMT35(void);
static void InitiateMT36(void);
static void InitiateMT37(void);
static void ChargerDivider50(uint32_t Voltage,uint32_t Current);


ModuMsg ModuleMsg;
MotorMsg MonitorMsg;

uint32_t ModuleVoltage;
uint32_t ModuleCurrent[8];                                                       //����ģ�����
static uint8_t  PowerDividerFlag;


void ModuleMain (void)
{   
	ModuleMsg.Cnt = 0;
	MonitorMsg.Cnt = 0;
	ModuleMsg.StartFlag = 0;                                                       // ������ʶ
	ChargerMsg.PreCharge= 0;
	//tudo
	ModuleMsg.NOcount = 1;    //ģ������
  ModuleMsg.ModuleType=0;   //ģ������
	
  while (1) 
 {	 
	  OSTimeDlyHMSM(0,0,0,20);
	  ModuleMsg.Cnt++;
	  MonitorMsg.Cnt++;
		Module_RECData_Pro();

/***************************************************************************************************
	                              ���ģ��˵����ݴ���
**************************************************************************************************/	

 //       ����ģ����ͳһ�ĳ���	
	if (((ModuleMsg.Cnt%200)==0)&&(ModuleMsg.ModuleType==0))	                         //����
	{	 	 
		ModuleSet(5,0,0,0);	 
	}
	 
	if ((ModuleMsg.Cnt%25)==0)	 
	{
					 if(ChargerMsg.ChargeStage==2)                                               // ��Ե���״̬
					 {
							 if(BMSMessage.MAXVoltage<=ChargerMsg.MAXVoltage)      //�綨��Ե����ѹ
							 {
									ChargerMsg.InsuVoltage=BMSMessage.MAXVoltage;
									if(ChargerMsg.InsuVoltage<=2000)
										ChargerMsg.InsuVoltage=2000;						
							 }
							 else
							 {
									ChargerMsg.InsuVoltage=ChargerMsg.MAXVoltage;			 
							 }
							 ChargerMsg.InsuCurrent=ModuleMsg.NOcount*200;                                             //�綨��Ե������					 			 
							if(	ModuleMsg.StartFlag == 0)
							 {
  								ModuleSet(2,ChargerMsg.InsuVoltage,ChargerMsg.InsuCurrent,ModuleMsg.ModuleType);	     // ������Ե���
								 	OSTimeDlyHMSM(0,0,0,20);
								 	ModuleMsg.StartFlag=1;                                                                 // ������ʶ
							 } 
              else{
                  ModuleSet(1,ChargerMsg.InsuVoltage,ChargerMsg.InsuCurrent,ModuleMsg.ModuleType);	     //�������޸ĵ�ѹ ����
						      }							 
							 if((ChargerMsg.InsuVoltage-ModuleMsg.OutVoltage)<=100)
							 {
								   if(InsulationFlag==0)
										 {
											 DC_SWITCH_ON();						
							         ChargerMsg.DCSwitchFlag=1;
											 InsulationFlag=1;
											}  										 
							 }
                if(InsulationFlag==2)
										 {
											  ModuleSet(4, 0, 0,0);
											  OSTimeDlyHMSM(0,0,1,0);
											  ModuleMsg.StartFlag=0;
											 	DC_SWITCH_OFF();						
							          ChargerMsg.DCSwitchFlag=0;
											  InsulationFlag=3;
										 }							 
		   }		
		 if(ChargerMsg.ChargeStage==7)                       // ���״̬
		  {
				if(BMSMessage.BatteryChgAlow	== 0x10)                                                  //�������
				{
						if(ChargerMsg.PreCharge==0)                                                         //Ԥ������                                        
						{
								 if(BMSMessage.RequestVoltage<=BMSMessage.BatteryVoltage)                       //�綨�����ѹ
								 {
										 BMSMessage.RequestVoltage=BMSMessage.BatteryVoltage-50;
								 }
								 if(	ModuleMsg.StartFlag == 0)
								 {
										ModuleSet(3,BMSMessage.BatteryVoltage-50,ModuleMsg.NOcount*200,ModuleMsg.ModuleType);	// ����Ԥ��
										OSTimeDlyHMSM(0,0,0,20); 
										ModuleMsg.StartFlag=1;                                            // ������ʶ
										AnalyseMT31();                                                    // �������	
								 }
                 else{
								    ModuleSet(1,BMSMessage.RequestVoltage,BMSMessage.RequestCurrent*10/ModuleMsg.NOcount,ModuleMsg.ModuleType);
								 }								 
								 if((BMSMessage.BatteryVoltage-ModuleMsg.OutVoltage)<=100)
								 {

											DC_SWITCH_ON();                                              //����ֱ���Ӵ���
											OSTimeDlyHMSM(0,0,0,20);								 
											ChargerMsg.DCSwitchFlag=1;
											ChargerMsg.PreCharge=1;	                                     // Ԥ���ʶ										 
								 }
					   	}
					 else{                                    //ģ���·�ָ��Զ������л�����
//									if(PowerDividerFlag==0)//���л�
//									{
											 ModuleSet(1, BMSMessage.RequestVoltage, BMSMessage.RequestCurrent*10/ModuleMsg.NOcount,ModuleMsg.ModuleType);         //�������
//											if(BMSMessage.RequestVoltage*BMSMessage.RequestCurrent*10>=BMSMessage.RequestVoltage*ModuleMsg.MAXCurrent*10*ModuleMsg.NOcount)
//											{
//													ChargerDivider50(BMSMessage.RequestVoltage,BMSMessage.RequestCurrent);				                                     //���͹��ʷ�������			
//											}
//									}
//									else if(PowerDividerFlag==1)
//									{//�л�																		
//											 ModuleSet(1, BMSMessage.RequestVoltage, BMSMessage.RequestCurrent*10/ModuleMsg.NOcount/2,ModuleMsg.ModuleType);        //������������																
//									 }						
				         }
						}
          else if(BMSMessage.BatteryChgAlow	== 0x00)                                               //����ֹ
					{		
             ModuleSet(4, 0, 0,0);
						 if((ChargerMsg.DCSwitchFlag==1)&&(ChargerMsg.ChargeCurrent<=50))                      //ͣ���������Ͽ��Ӵ���                                            
							{						
								DC_SWITCH_OFF();
								ChargerMsg.DCSwitchFlag=0;				
							 }						
					}					 
	    }		
		if((ChargerMsg.ChargeStage!=0)&&(ChargerMsg.ChargeStage!=2)&&(ChargerMsg.ChargeStage!=7))
		{
			 if(ModuleMsg.StartFlag==1)
			 { 
				 ModuleSet(4, 0, 0,0);		
			 }					 
				if(ChargerMsg.DCSwitchFlag==0)
				{
					ModuleMsg.StartFlag=0;						
				}					
		} 
			
}		
 
/***************************************************************************************************
	                             ��ض˵����ݴ���
**************************************************************************************************/
	
   if(((MonitorMsg.Cnt)%50)==0)
	 {
	   InitiateMT34();	 
	 }

	 if(ChargerMsg.StartCompleteflag==1)
		 {
		   InitiateMT31();
			 ChargerMsg.StartCompleteflag=2;
		 }
	 }	
} 

static void	Module_RECData_Pro(void)  
{	
/***************************************************************************************************************************************
*	����ѭ���Ĵ����ٶȸ������жϵĴ����ٶȣ������һ�������������ж�д�����ݣ�����ѭ���������ݣ�ÿ������һ֡���ݣ���Ѹ������ݶ�����
* �������ݻ����������ݳ��ȴ�С���ޣ����жϵ�дָ��ԶԶ�������Ķ�ָ���ٶȣ����ǻ���ֶ�������
***************************************************************************************************************************************/
  	if(prMsgCAN1==&MsgCAN1BUF[CAN1_MSG_NUMBER-1])    /* Ԥ��һ���洢��Ԫ���洢����ֹдָ��ָ�����һ���洢��Ԫʱ����ָ�����ʱ���    */
	  {
			MessageCAN1 = *prMsgCAN1;
		  memset(prMsgCAN1,0,sizeof(*prMsgCAN1));        /*������һ֡���ݣ��Ͷ����ð�����                                                 */			
			prMsgCAN1=MsgCAN1BUF;			                     /* ����ָ��ָ�� ����β��ָ��ʼ                                                 */
	  }
	  else                                             
		{
	     MessageCAN1 = *prMsgCAN1;
		   memset(prMsgCAN1,0,sizeof(*prMsgCAN1));       /*������һ֡���ݣ��Ͷ����ð�����                                                 */
		   prMsgCAN1 ++;                                 /*ָ��������������󣬷�ָֹ�����������ظ���if����                           */
	  }
			
    switch(MessageCAN1.CANID)
	 {
/***************************************************************************************************
	                              ���ģ��˵����ݴ���
**************************************************************************************************/	
//        ����ģ����ͳһ����������		 8��ģ��

						 case 0x1820a080 :               
										ModuleMsg.OutVoltage=  MessageCAN1.DATAA>>16;
										ModuleCurrent[0]=  MessageCAN1.DATAB&0xffff;
								 break ;
						 
						 case 0x1820a081 :               
										ModuleCurrent[1]=MessageCAN1.DATAB&0xffff;
								 break ;
						 
						 case 0x1820a082 :               
										ModuleCurrent[2]=MessageCAN1.DATAB&0xffff;
								 break ;
						 
						 case 0x1820a083 :               
										ModuleCurrent[3]=MessageCAN1.DATAB&0xffff;
								 break ;
						 
						 case 0x1820a084 :               
										ModuleCurrent[4]=MessageCAN1.DATAB&0xffff;
								 break ;
						 
						 case 0x1820a085 :               
										ModuleCurrent[5]=MessageCAN1.DATAB&0xffff;
								 break ;

						 case 0x1820a086 :               
										ModuleCurrent[6]=MessageCAN1.DATAB&0xffff;
								 break ;
						 
						 case 0x1820a087 :               
										ModuleCurrent[7]=MessageCAN1.DATAB&0xffff;
								 break ;

//        Ӣ��ԴЭ�� 
						 case 0x02c8f000:               
										ModuleMsg.OutVoltage=(MessageCAN1.DATAA&0xffffff)/100;
										ModuleCurrent[0]=(MessageCAN1.DATAB&0xffff)/10;
								 break ;

						 case 0x02c8f001:               
										ModuleMsg.OutVoltage=(MessageCAN1.DATAA&0xffffff)/100;
										ModuleCurrent[1]=(MessageCAN1.DATAB&0xffff)/10;
								 break ;

						 case 0x02c8f002:               
										ModuleMsg.OutVoltage=(MessageCAN1.DATAA&0xffffff)/100;
										ModuleCurrent[2]=(MessageCAN1.DATAB&0xffff)/10;
								 break ;

						 case 0x02c8f003:               
										ModuleMsg.OutVoltage=(MessageCAN1.DATAA&0xffffff)/100;
										ModuleCurrent[3]=(MessageCAN1.DATAB&0xffff)/10;
								 break ;


					 
										
										
/***************************************************************************************************
	                             ��ض˵����ݴ���
**************************************************************************************************/		
//Aǹ������ݴ���
		 case 0x183500a0:                //ң��֡ 			 
					 AnalyseMT35();			 
		     break ;
		 
		 case 0x103000a0:                  //�������֡
			 if(Sys_PARA.ChargerNO==0){			 
			     AnalyseMT30();
			   }
		     break ;		
				 

		 case 0x103100a0:                  //�������֡
		     break ;		 
		 
		 case 0x103200a0:                  //ֹͣ���֡     
			 if(Sys_PARA.ChargerNO==0){	
			   AnalyseMT32();
			 }		 
		     break ;	

		 case 0x103300a0:                  //�������֡
			   AnalyseMT33();		
					break ; 
			 
					 
//Bǹ������ݴ���					 
		 case 0x183501a0: 			  
			 if(Sys_PARA.ChargerNO==1){		 
        if((MessageCAN1.DATAA&0xff)==0x05)
		    {			          
			   AnalyseMT35();		
		     }
			 }
		     break ;
		 
		 case 0x103001a0:                  //�������֡
			 	if(Sys_PARA.ChargerNO==1){
			   AnalyseMT30();
				}
		     break ;		 

		 case 0x103101a0:                  //�������֡
		     break ;		 
		 
		 case 0x103201a0:                  //ֹͣ���֡     
			   if(Sys_PARA.ChargerNO==1){
			   AnalyseMT32();
				 }
		     break ;	

		 case 0x103301a0:                  //�������֡
			   AnalyseMT33();
		     break ;	


	 	 default:
			   break ;		 				 
	 }
	 	 
	 memset(&MessageCAN1,0,sizeof(MessageCAN1));//���CAN�����ݣ� ��ֹ�ظ�����

}


/**************************************************************************************************************
   ģ��ĺ�������
**************************************************************************************************************/

void ModuleSet(uint8_t CMD, uint16_t V, uint16_t I,uint8_t ModuleType)
{
     uint8_t i;
	if(ModuleMsg.ModuleType==0)                                   //����Э��
	{			
				for(i=0;i<ModuleMsg.NOcount;i++)
				{
							switch(CMD)
							 {	
								 case 1:
									 CAN1ID=0x180180a0|(i<<8);                     //���õ�ѹ����
									 if(V>5000)
									 {
										 CAN1_Data[0]=0x75;
									 }
									 else
									 {
										 CAN1_Data[0]=0x65;
									 }							 
									 CAN1_Data[1]=0x00;
									 CAN1_Data[2]=V&0xff;
									 CAN1_Data[3]=(V>>8)&0xff;
									 CAN1_Data[4]=I&0xff;
									 CAN1_Data[5]=(I>>8)&0xff;
									 CAN1_Data[6]=0x0c; 			
									 CAN1_Data[7]=0x17;
									 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
										break;
									 
								 case 2:	 
									 CAN1ID=0x180180a0|(i<<8);                      //���ٿ���
										if(V>5000)
									 {
										 CAN1_Data[0]=0x11;
									 }
									 else
									 {
										 CAN1_Data[0]=0x01;
									 }	
									 CAN1_Data[0]=0x01;
									 CAN1_Data[1]=0x00;
									 CAN1_Data[2]=V&0xff;
									 CAN1_Data[3]=(V>>8)&0xff;
									 CAN1_Data[4]=I&0xff;
									 CAN1_Data[5]=(I>>8)&0xff;
									 CAN1_Data[6]=0x6c;
									 CAN1_Data[7]=0x07;		 
									 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
										break;
									 
								 case 3:	 
									 CAN1ID=0x180180a0|(i<<8);                      //���𿪻�
										if(V>5000)
									 {
										 CAN1_Data[0]=0x11;
									 }
									 else
									 {
										 CAN1_Data[0]=0x03;
									 }	
									 CAN1_Data[0]=0x01;
									 CAN1_Data[1]=0x00;
									 CAN1_Data[2]=V&0xff;
									 CAN1_Data[3]=(V>>8)&0xff;
									 CAN1_Data[4]=I&0xff;
									 CAN1_Data[5]=(I>>8)&0xff;
									 CAN1_Data[6]=0x6c;
									 CAN1_Data[7]=0x07;		 
									 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
										break;									 
						 
								 case 4:	 
									 CAN1ID=0x180180a0|(i<<8) ;                     //�ػ�
									 CAN1_Data[0]=0x02;
									 CAN1_Data[1]=0x00;
									 CAN1_Data[2]=0x00;
									 CAN1_Data[3]=0x00;
									 CAN1_Data[4]=0x00;
									 CAN1_Data[5]=0x00;
									 CAN1_Data[6]=0x00;
									 CAN1_Data[7]=0x00;					 
									 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
								 case 5:	 
									 CAN1ID=0x184080a0|(i<<8) ;                     //����
									 CAN1_Data[0]=0x00;
									 CAN1_Data[1]=0x00;
									 CAN1_Data[2]=0x00;
									 CAN1_Data[3]=0x00;
									 CAN1_Data[4]=0x00;
									 CAN1_Data[5]=0x00;
									 CAN1_Data[6]=0x00; 
									 CAN1_Data[7]=0x00;					 
									 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
										break;
								 default:
										break;			 		 
						 }	
      	}
      }
	else if(ModuleMsg.ModuleType==1)                              //Ӣ��ԴЭ��
	{
				for(i=0;i<ModuleMsg.NOcount;i++)
				{
							switch(CMD)
							 {	
								 case 1:
									 CAN1ID=0x02DB00F0|(i<<8);                     //���õ�ѹ����
										 
									 CAN1_Data[0]=0x00;
									 CAN1_Data[1]=(V*100>>16)&0xff;
									 CAN1_Data[2]=(V*100>>8)&0xff;
									 CAN1_Data[3]=(V*100)&0xff;
									 CAN1_Data[4]=0x00;
									 CAN1_Data[5]=(V*100>>16)&0xff;; 			
									 CAN1_Data[6]=(V*100>>8)&0xff;
									 CAN1_Data[7]=(V*100)&0xff; 							 					 
									 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
										break;
									 
								 case 2:	 
									 CAN1ID=0x02DA00F0|(i<<8);                      //���ٿ���								 
									 CAN1_Data[0]=0x00;
									 CAN1_Data[1]=0x00;
									 CAN1_Data[2]=0x00;
									 CAN1_Data[3]=0x00;
									 CAN1_Data[4]=0x00;
									 CAN1_Data[5]=0x00;
									 CAN1_Data[6]=0x00;
									 CAN1_Data[7]=0x00;		 
									 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
										break;
								 
								 case 3:
									  break;
								 case 4:	 
									 CAN1ID=0x02DA00F0|(i<<8);                     //�ػ�
									 CAN1_Data[0]=0x01;
									 CAN1_Data[1]=0x00;
									 CAN1_Data[2]=0x00;
									 CAN1_Data[3]=0x00;
									 CAN1_Data[4]=0x00;
									 CAN1_Data[5]=0x00;
									 CAN1_Data[6]=0x00;
									 CAN1_Data[7]=0x00;					 
									 WriteCAN1(8,1, CAN1ID,CAN1_Data);	

								 default:
										break;			 		 
						 }
							 OSTimeDlyHMSM(0,0,0,5);
					}
	 }	 	
}

//��ȡģ����Ϣ   �ݶ���ȡ8��ģ��
void ModuleGet(uint8_t CMD,uint32_t Voltage,uint32_t Current,uint8_t err)
{
	  uint8_t i;
	  uint32_t Isum;
	if(ModuleMsg.ModuleType==0)                                    //����Э��
			{
					switch (CMD)
					{
						case 0:							
								break;
								
						case 1:
								break;
						
						case 2:
								break;		
					
						default:
								break;
															
					 }
		 }		
	 else if(ModuleMsg.ModuleType==1)                             //Ӣ��ԴЭ��
	 {
					switch (CMD)
					{
						case 0:                                             //�������ѹ�͵���
							 for(i=0;i<ModuleMsg.NOcount;i++)
			          {	
								 CAN1ID=0x02C800F0|(i<<8);						
								 CAN1_Data[0]=0x00;
								 CAN1_Data[1]=0x00;
								 CAN1_Data[2]=0x00;
								 CAN1_Data[3]=0x00;
								 CAN1_Data[4]=0x00;
								 CAN1_Data[5]=0x00;
								 CAN1_Data[6]=0x00; 
								 CAN1_Data[7]=0x00;				
								 WriteCAN1(8,1, CAN1ID,CAN1_Data);
								}									
								break;
								
						case 1:
								CAN1ID=0x02C600F0|(i<<8);                           //�������ѹ						
								 CAN1_Data[0]=0x00;
								 CAN1_Data[1]=0x00;
								 CAN1_Data[2]=0x00;
								 CAN1_Data[3]=0x00;
								 CAN1_Data[4]=0x00;
								 CAN1_Data[5]=0x00;
								 CAN1_Data[6]=0x00; 
								 CAN1_Data[7]=0x00;				
								 WriteCAN1(8,1, CAN1ID,CAN1_Data);															
								break;
						
						case 2:
								CAN1ID=0x02C400F0|(i<<8);                           //��ģ�����״̬
						
								 CAN1_Data[0]=0x00;
								 CAN1_Data[1]=0x00;
								 CAN1_Data[2]=0x00;
								 CAN1_Data[3]=0x00;
								 CAN1_Data[4]=0x00;
								 CAN1_Data[5]=0x00;
								 CAN1_Data[6]=0x00; 
								 CAN1_Data[7]=0x00;				
								 WriteCAN1(8,1, CAN1ID,CAN1_Data);					
								break;		
											
						default:
								break;											
					
				}

			}				 
			OSTimeDlyHMSM(0,0,0,5);
			for(i=0;i<ModuleMsg.NOcount;i++)
			{
				Isum= Isum + ModuleCurrent[i];					
			}
			 ModuleMsg.OutCurrent=Isum/10;								
}


/**************************************************************************************************************
  ��صĺ�������
**************************************************************************************************************/
void AnalyseMT30(void)
{	
	    ChargerMsg.ChargeStage=1;	
		  InitiateMT30();	
}

void AnalyseMT31(void)
{	
		  InitiateMT31();
}

void AnalyseMT32(void)
{	
	    ChargerMsg.ChargeStage=8;
	    InitiateMT35();	
}

void AnalyseMT33(void)
{	
		 InitiateMT33();
}

void AnalyseMT34(void)
{	
	
}


void AnalyseMT35(void)
{		
		if((MessageCAN1.DATAA&0xff)==0x01)
		{	
			ChargerMsg.ChargeVoltage =  MessageCAN1.DATAA>>8;
			ChargerMsg.ChargeCurrent =  MessageCAN1.DATAB>>8;
	  }
		 if(Sys_PARA.ChargerNO==0)
		{
			if((MessageCAN1.DATAA&0xff)==0x05)
			{			       
					InitiateMT35();		
			 }
		 }	   
}

void InitiateMT30(void)
{	
		 if(Sys_PARA.ChargerNO==0){	
			 CAN1ID=0x1030a000;  
	  }else{
			 CAN1ID=0x1030a001; 
		}	 
			 CAN1_Data[0]=0x00;
			 CAN1_Data[1]=0x00;
			 CAN1_Data[2]=0x00;
			 CAN1_Data[3]=0x00;
			 CAN1_Data[4]=0x00;
			 CAN1_Data[5]=0x00;
			 CAN1_Data[6]=0x00;
			 CAN1_Data[7]=0x00;		
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);
}
void InitiateMT31(void)
{	
	 if(Sys_PARA.ChargerNO==0){	
			 CAN1ID=0x1031a000;  
	  }else{
			 CAN1ID=0x1031a001; 
		}		 	
			 CAN1_Data[0]=0x01;
			 CAN1_Data[1]=0x00;
			 CAN1_Data[2]=0x00;
			 CAN1_Data[3]=0x00;
			 CAN1_Data[4]=0x00;
			 CAN1_Data[5]=0x00;
			 CAN1_Data[6]=0x00;	
			 CAN1_Data[7]=0x00;		
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);

			 CAN1_Data[0]=0x02;
			 CAN1_Data[1]=0x00;
			 CAN1_Data[2]=0x04;
			 CAN1_Data[3]=0x78;
			 CAN1_Data[4]=0x4c;
			 CAN1_Data[5]=0x1d;
			 CAN1_Data[6]=0xa4;		
			 CAN1_Data[7]=0x01;			
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);

			 CAN1_Data[0]=0x03;
			 CAN1_Data[1]=0xd0;
			 CAN1_Data[2]=0x07;
			 CAN1_Data[3]=0x44;
			 CAN1_Data[4]=0x02;
			 CAN1_Data[5]=0x40;
			 CAN1_Data[6]=0x02;		
			 CAN1_Data[7]=0x08;					 
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);

			 CAN1_Data[0]=0x04;
			 CAN1_Data[1]=0x07;
			 CAN1_Data[2]=0xf4;
			 CAN1_Data[3]=0x01;
			 CAN1_Data[4]=0x58;
			 CAN1_Data[5]=0x02;
			 CAN1_Data[6]=0xff;
			 CAN1_Data[7]=0xff;					 
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);

			 CAN1_Data[0]=0x05;
			 CAN1_Data[1]=0xff;
			 CAN1_Data[2]=0xff;
			 CAN1_Data[3]=0xff;
			 CAN1_Data[4]=0xff;
			 CAN1_Data[5]=0xff;
			 CAN1_Data[6]=0xff;	
			 CAN1_Data[7]=0xff;					 
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);

			 CAN1_Data[0]=0x06;
			 CAN1_Data[1]=0xff;
			 CAN1_Data[2]=0xff;
			 CAN1_Data[3]=0xff;
			 CAN1_Data[4]=0xff;
			 CAN1_Data[5]=0xff;
			 CAN1_Data[6]=0xff;	
			 CAN1_Data[7]=0xff;					 
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);

			 CAN1_Data[0]=0x07;
			 CAN1_Data[1]=0xff;
			 CAN1_Data[2]=0xff;
			 CAN1_Data[3]=0xff;
			 CAN1_Data[4]=0xff;
			 CAN1_Data[5]=0xff;
			 CAN1_Data[6]=0xff;	
			 CAN1_Data[7]=0xff;					 
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);
}
void InitiateMT32(void)
{	
		 if(Sys_PARA.ChargerNO==0){	
			 CAN1ID=0x1032a000;  
	  }else{
			 CAN1ID=0x1032a001; 
		}		                       
			 CAN1_Data[0]=0x00;
			 CAN1_Data[1]=0x00;
			 CAN1_Data[2]=0x00;
			 CAN1_Data[3]=0x00;
			 CAN1_Data[4]=0x00;
			 CAN1_Data[5]=0x00;
			 CAN1_Data[6]=0x00;			
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);
}
void InitiateMT33(void)
{	
		 if(Sys_PARA.ChargerNO==0){	
			 CAN1ID=0x1033a000;  
	  }else{
			 CAN1ID=0x1033a001; 
		}	                    
			 CAN1_Data[0]=0x00;
			 CAN1_Data[1]=0x00;
			 CAN1_Data[2]=0x00;
			 CAN1_Data[3]=0x00;
			 CAN1_Data[4]=0x00;
			 CAN1_Data[5]=0x00;
			 CAN1_Data[6]=0x00;			
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);
}
void InitiateMT34(void)
{	
		 if(Sys_PARA.ChargerNO==0){	
			 CAN1ID=0x1834a000;  
	  }else{
			 CAN1ID=0x1834a001; 
		}	  
    if(ADstatus == ADC4V)	
     {
			 CAN1_Data[0]=1<<2;
     }
		 else{
			 CAN1_Data[0]=0x00;
		 }
			 CAN1_Data[1]=0x00;
			 CAN1_Data[2]=0x00;
			 CAN1_Data[3]=0x00;
			 CAN1_Data[4]=0x00;
			 CAN1_Data[5]=0x00;
			 CAN1_Data[6]=0x00;			
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);
}
void InitiateMT35(void)
{	
		 if(Sys_PARA.ChargerNO==0){	
			 CAN1ID=0x1835a000;  
	  }else{
			 CAN1ID=0x1835a001; 
		}	                      
			 CAN1_Data[0]=0x01;
			 CAN1_Data[1]=0x04;
			 CAN1_Data[2]=ChargerMsg.ChargeVoltage&0xff;
			 CAN1_Data[3]=(ChargerMsg.ChargeVoltage>>8)&0xff;
			 CAN1_Data[4]=(4000-ChargerMsg.ChargeCurrent)&0xff;
			 CAN1_Data[5]=((4000-ChargerMsg.ChargeCurrent)>>8)&0xff;
			 CAN1_Data[6]=BMSMessage.SOC;			
	 		 CAN1_Data[7]=BMSMessage.MINBatteryTemp;		
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
	 
	     CAN1_Data[0]=0x02;
			 CAN1_Data[1]=BMSMessage.MAXBatteryTemp;
			 CAN1_Data[2]=BMSMessage.MAXSingleVoltage&0xff;
			 CAN1_Data[3]=(BMSMessage.MAXSingleVoltage>>8)&0xff;
			 CAN1_Data[4]=0x00;
			 CAN1_Data[5]=0x00;
			 CAN1_Data[6]=BMSMessage.RequestVoltage&0xff;			
	 		 CAN1_Data[7]=(BMSMessage.RequestVoltage>>8)&0xff;	 	 
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);	 
	 
	     CAN1_Data[0]=0x03;
			 CAN1_Data[1]=(4000-BMSMessage.RequestCurrent)&0xff;
			 CAN1_Data[2]=((4000-BMSMessage.RequestCurrent)>>8)&0xff;
			 CAN1_Data[3]=BMSMessage.RequestChargeMode;
			 CAN1_Data[4]=BMSMessage.BCSdetVoltage&0xff;
			 CAN1_Data[5]=(BMSMessage.BCSdetVoltage>>8)&0xff;
			 CAN1_Data[6]=(4000-BMSMessage.BCSdetCurrent)&0xff;			
	 		 CAN1_Data[7]=((4000-BMSMessage.BCSdetCurrent)>>8)&0xff;				 			 
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
			 
	     CAN1_Data[0]=0x04;
			 CAN1_Data[1]=BMSMessage.RemainTime&0xff;
			 CAN1_Data[2]=(BMSMessage.RemainTime>>8)&0xff;
			 CAN1_Data[3]=0x00;
			 CAN1_Data[4]=0x00;
			 CAN1_Data[5]=0x00;
			 CAN1_Data[6]=0x00;			
	 		 CAN1_Data[7]=0x00;				 
			 WriteCAN1(8,1, CAN1ID,CAN1_Data);	
}
void InitiateMT36(void)
{	
			 if(Sys_PARA.ChargerNO==0){	
			 CAN1ID=0x1835a000;  
	  }else{
			 CAN1ID=0x1835a001; 
		}
	
	
	
	
	
}
void InitiateMT37(void)
{	
			 if(Sys_PARA.ChargerNO==0){	
			 CAN1ID=0x1835a000;  
	  }else{
			 CAN1ID=0x1835a001; 
		}
	
	
	
}

/**************************************************************************************************************
 ����Ĵ�����
**************************************************************************************************************/
void ChargerDivider50(uint32_t Voltage,uint32_t Current)
{	
	 if(Sys_PARA.ChargerNO==0){	
			 CANID=0x1D500b0a;  
	  }else{
			 CANID=0x1D500a0b; 
		}	 
			 CAN_Data[0]=Voltage&0xff;
			 CAN_Data[1]=(Voltage>>8)&0xff;
			 CAN_Data[2]=Current&0xff;
			 CAN_Data[3]=(Current>>8)&0xff;
			 CAN_Data[4]=0x00;
			 CAN_Data[5]=0x00;
			 CAN_Data[6]=0x00;		
	 if(Sys_PARA.ChargerNO==0){	
			 CAN_Data[7]=0x0a;  
	  }else{
			 CAN_Data[7]=0x0b;  
		}	
			 WriteCAN1(8,1, CANID,CAN_Data);	
}

void ChargerDivider51(uint32_t Voltage,uint32_t Current)
{	
	 if(Sys_PARA.ChargerNO==0){	
			 CANID=0x1D510b0a;  
	  }else{
			 CANID=0x1D510a0b; 
		}	
    if(ChargerMsg.ChargeStage==0)
		{			
			 CAN_Data[0]=0x00;
		}
			 CAN_Data[1]=0x00;
			 CAN_Data[2]=0x00;
			 CAN_Data[3]=0x00;
			 CAN_Data[4]=0x00;
			 CAN_Data[5]=0x00;
			 CAN_Data[6]=0x00;		
	
			 WriteCAN1(8,1, CANID,CAN_Data);	
}
