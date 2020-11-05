/****************************************Copyright (c)****************************************************
**                                 Tomorn electronics Co.,LTD.
**                                     
**                                 http://www.tomorn.cn
**                                      wujikun
**--------------File Info---------------------------------------------------------------------------------
** File Name:               Main.c
** Last modified Date:      2018.05.18
** Last Version:            1.0
** Description:             The main function  ������
*********************************************************************************************************/

#include <includes.h>
#include <cortexm3.h>
#include <module.h>

/*********************************************************************************************************
 �궨��
*********************************************************************************************************/

/*********************************************************************************************************
  VARIABLES ����
*********************************************************************************************************/
static OS_STK  GstkStart[TASK_START_STK_SIZE];                            /*  ��������Ķ�ջ            */
static OS_STK  GstkADC[TASK_ADC_STK_SIZE];                                /*  BMSͨѶ����Ķ�ջ         */
static OS_STK  GstkBMS[TASK_BMS_STK_SIZE];                                /*  BMSͨѶ����Ķ�ջ         */
static OS_STK  GstkModule[TASK_Module_STK_SIZE];                                          
static OS_STK  GstkInsulation[TASK_Insulation_STK_SIZE];                  /*  4G����Ķ�ջ              */

/*********************************************************************************************************
   FUNCTION PROTOTYPES ��������
*********************************************************************************************************/
static void taskStart (void  *parg);                                      /*  The start task  ��������  */
static void taskADC(void  *parg);
static void taskBMS(void  *parg);
static void taskModule(void  *parg);
static void taskInsulation(void  *parg);
static void SystemParameterInit(void);

SYS_PARA   Sys_PARA;

/*********************************************************************************************************
** Function name:	      main
** Descriptions:	      �������
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int main (void)
{    
		GPIOInit();
	  ADCInit(400000);
	  SSP0_Init();
	  SSP2_Init();
	  Timer0Init();
	  EepromInit();
	  UART0Init();
	  UART1Init(); 
	  UART2Init();
	  UART3Init();	
    UART4Init();
	 
	  CAN_Init(0, BPS_250K);
	  CAN_Init(1, BPS_125K);
	
	  ExRTCSet(&RTCtimedate);                                             /*�ṹ�崫��ʱ�����ݽṹ��ĵ�ַ*/
    RTCInit (&RTCtimedate);	                                            /*�ṹ�崫��ʱ�����ݽṹ��ĵ�ַ*/
	
	  SystemParameterInit();		 
		
    OSInit();                                                           /*  ��ʼ���ں�                  */                                                                   
	  OSTaskCreate (taskStart,                                          
						   (void *)0, 
				       &GstkStart[TASK_START_STK_SIZE-1],  
			      	 TASK_START_PRIO );                                     /*  Initialize the start task   */							 
																																			/*  ��ʼ����������              */ 
 	 if(PRINT_STRING)
	  Print("%s\n", "OS Start  !");							 
	  OSStart();                                                        /*  Start uC/OS-II ����uC/OS-II */
	  return(0) ;
}

/*********************************************************************************************************
** Function name:           taskStart	   
** Descriptions:            Start task	
** input parameters:        *parg
** output parameters:       ��      
** Returned value:          �� 
*********************************************************************************************************/
static void taskStart (void  *parg)
{
    (void)parg;
		tick_init();
    #if OS_TASK_STAT_EN > 0
    OSStatInit();                                                      /*  ʹ��ͳ�ƹ���                */
    #endif

  	/*
     *  Create the other tasks here. �����ﴴ����������
     */
	  OSTaskCreate (taskADC, 
								 (void *)0,   		
			            &GstkADC[TASK_ADC_STK_SIZE-1], 
				          TASK_ADC_PRIO);
								 
	  OSTaskCreate (taskBMS, 
								 (void *)0,   		
			            &GstkBMS[TASK_BMS_STK_SIZE-1], 
				          TASK_BMS_PRIO);	
								 
	  OSTaskCreate (taskModule, 
								 (void *)0,   		
			            &GstkModule[TASK_Module_STK_SIZE-1], 
				          TASK_Module_PRIO);
								 															 
	  OSTaskCreate (taskInsulation, 
								 (void *)0,   		
			            &GstkInsulation[TASK_Insulation_STK_SIZE-1], 
				          TASK_Insulation_PRIO);
								 
	while (1) 
		{  
			  if(PRINT_STRING)
		  	Print("%s\n", "OS Start Finished !");    
        OSTaskSuspend(OS_PRIO_SELF);                                    /*  The start task can be pended*/
                                                                        /*  here. ������������������  */
    }
}

/*********************************************************************************************************
** Function name:           other tasks	   
** Descriptions:            other tasks	
** input parameters:        *parg
** output parameters:       ��      
** Returned value:          �� 
*********************************************************************************************************/

static  void  taskADC(void  *parg)
{
	(void)parg;
	 if(PRINT_STRING)
	 Print("%s\n", "ADCMain Task Action !");
	 ADCMain();
}


static  void  taskBMS(void  *parg)
{
	(void)parg;
	 if(PRINT_STRING)
	 Print("%s\n", "BMSMain Task Action !");
	 BMSMain();
}

static  void  taskModule(void  *parg)
{
	(void)parg;
	 if(PRINT_STRING)
	 Print("%s\n", "ModuleMain Task Action !");
	 ModuleMain();
}

static  void  taskInsulation(void  *parg)
{	
	(void)parg;
	 if(PRINT_STRING)
	 Print("%s\n", "InsulationMain Task Action !");
	 InsulationMain();	 
}

/*********************************************************************************************************
** Function name:           SystemParameterInit	   
** Descriptions:            ϵͳ������ʼ��	
** input parameters:        ��
** output parameters:       ��      
** Returned value:          �� 
*********************************************************************************************************/

static void SystemParameterInit(void)
{			 	 
		// FramRead((uint8_t *)&Sys_PARA,SYS_PARA_ADDR,sizeof(Sys_PARA)); 
	   EepromRead(0, SYS_PARA_ADDR, (uint8_t *)&Sys_PARA, MODE_8_BIT, sizeof(Sys_PARA));
	  if(CHARGERNO_INT_Status()==0)
		{
			Sys_PARA.ChargerNO=0;
		}
		else{
			Sys_PARA.ChargerNO=1;
		}
	   ModuleMsg.NOcount=Sys_PARA.ModuleNOcount; 
     ModuleMsg.MAXVoltage=Sys_PARA.MAXVoltage;            // ��������ѹ
     ModuleMsg.MINVoltage=Sys_PARA.MINVoltage;            // ��С�����ѹ	
	   ModuleMsg.MAXCurrent=Sys_PARA.MAXCurrent;	          // ����������
	   ModuleMsg.MINCurrent=Sys_PARA.MINCurrent;	          // ��С�������
		
  	 if(PRINT_STRING)
	    Print("%s\n", "PARA Read !"); 				
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
