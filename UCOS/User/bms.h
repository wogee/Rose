#ifndef __BMS_H_
#define __BMS_H_
#include "LPC177x_8x.h"
#include "lpc_types.h"
#include "system_LPC177x_8x.h"
#include <ucos_ii.h>
#include "main.h"
#include  <can.h>
#include <gpio.h>
#include <print.h>
#include <main.h>
#include "calculator.h"
#include "fram.h"
#include "rtc.h"
typedef struct _MessageBMS
{   
	
	  uint8_t   BRMdatalen;           // BRM���ݳ���
	  uint8_t   BRMPackCount;         // BRM���ݳ���
	  uint16_t  BRMPNG;               // BRM���ݳ���	
	  uint8_t   CFGdatalen;           // CFG���ݳ���
	  uint8_t   CFGPackCount;         // CFG���ݳ���
	  uint16_t  CFGPNG;               // CFG���ݳ���			
	  uint8_t   BCSdatalen;           // BCS���ݳ���
	  uint8_t   BCSPackCount;         // BCS���ݳ���
	  uint16_t  BCSPNG;               // BCS���ݳ���		
//���ֲ���
    uint8_t   BHMflag;	
    uint8_t   BRMflag;	
	  uint16_t  SoftVersion;          // �汾��	
		uint8_t   BatteryType;          // �������
    uint16_t  RatedBatteryVolume;   // ��������
    uint16_t  RatedBatteryVoltage;  // ���ص�ѹ
    uint16_t  RatedBatteryEnergy;  // ���ص�ѹ	
//���ò���
    uint8_t   BCPflag;		
	  uint8_t   SOC;                  // SOC
    uint16_t  MAXVoltage;           // ��������ѹ
	  uint16_t  MAXCurrent;	          // ����������
	  uint16_t  BatteryVoltage;       // ��ص�ѹ		
//�������	
		uint8_t   BROflag;              //BMS׼������ 0=δ�յ�BRO��1=�յ��յ�BRO=0x00��2=�յ�BRO=0xAA
    uint16_t  RequestVoltage;       // �����ѹ
	  uint16_t  RequestCurrent;       // �������
		uint8_t   RequestChargeMode;    // ������ģʽ 
    uint8_t   BCLflag;              // ���յ�BCL��־
		uint8_t   BCL1flag;             // �״ν��յ�BCL��־
		uint8_t   BCS1flag;             // �״ν��յ�BCS��־
    uint8_t   BCSflag;		          // ����BCS��־
    uint8_t   BCSdataflag;					
//��״̬����		
    uint8_t   MAXSingleVoltageNO;	  // ��ߵ����ѹ���
    uint8_t   MAXBatteryTemp;	      // ��ߵ���¶�
    uint8_t   MAXBatteryTempNO;	    // ��ߵ���¶ȱ��		
    uint8_t   MINBatteryTemp;	      // ��͵���¶�
    uint8_t   MINBatteryTempNO;	    // ��͵���¶ȱ��
    uint8_t   SingleVoltageOHOL;    // �����ѹ���߹���
    uint8_t   SOCOHOL;              // SOC���߻��߹���
    uint8_t   BatteryOC;            // ��س�����
    uint8_t   BatteryTempOH;        // ��س�����
		uint8_t   BatteryInsuFlag;      // ��ؾ�Ե״̬
		uint8_t   BatteryCnetFlag;		  // ������״̬
		uint8_t   BatteryChgAlow;       // �������
		uint16_t  ChargeSuspendTime;    // �����ͣʱ��
//��������
		uint16_t  BCSdetVoltage;	      // ������������ѹ
	  uint16_t  BCSdetCurrent;        // ��������������		
		uint16_t  MAXSingleVoltage;	    // ����������ѹ
	  uint16_t  MINSingleVoltage;		  // ����������ѹ
	  uint16_t  RemainTime;		        // ʣ��ʱ�����
    uint16_t  SingleVoltage;        // �����ѹ
	  uint8_t   MAXSingleVoltageTemp; // ����������¶�
	  uint8_t   MINSingleVoltageTemp;	// ����������¶�
	  uint8_t   SingleVoltageTemp;    // �����¶�
		uint8_t   VIN[17];		          // ����ʶ���� ASCII��
	  uint8_t   CS;                   // У��λ
//ֹͣ����ԭ��	
    uint8_t   BSTflag;
    uint8_t   BSDflag;				
}BMSMsg;

extern BMSMsg BMSMessage;

typedef struct _MessageCharger
{	
	   uint8_t   ChargeStage;          // ���׶�
     uint16_t  ChargeVoltage;                                         
     uint16_t  ChargeCurrent; 
	   uint32_t  ChargerEnergy;
	   uint16_t  ChargedTime;
     uint16_t  InsuVoltage;           // ��Ե����ѹ
	   uint16_t  InsuCurrent;	          // ��Ե������	
     uint16_t  MAXVoltage;            // ��������ѹ
     uint16_t  MINVoltage;            // ��������ѹ	
	   uint16_t  MAXCurrent;	          // ����������
	   uint16_t  MINCurrent;	          // ����������	
     uint16_t  CHMcnt;
     uint16_t  CRMcnt;
     uint16_t  CMLcnt;
     uint16_t  CTScnt;
     uint16_t  CROcnt;
     uint16_t  BCLcnt;	
     uint16_t  BCScnt;		
     uint16_t  CCScnt;
	   uint16_t  CSTcnt;
	   uint16_t  BSDcnt;		 
	   uint16_t  CSDcnt;
	   uint16_t  CEMcnt;		 
		 uint16_t  Stopcnt;              //��ʱֹͣ
		 uint8_t   SE12SwitchFlag;       //������Դ���ϱ�־
	   uint8_t   DCSwitchFlag;         //ֱ���Ӵ������ϱ�־
		 uint8_t   StartCompleteflag;    //�����ɹ���־
     uint8_t   StopCompleteflag;     //ֹͣ�ɹ���־
	   uint8_t   PreCharge;		 		     //Ԥ���־
	   uint32_t  StopReason;		
}ChargeMsg;
extern ChargeMsg ChargerMsg;

typedef struct _SwitchStatus
{		
	   uint8_t   EMGStat;               // ��ͣ
	   uint8_t   DoorStat;              // �Ž�
	   uint8_t   ELockerStat;           // ����� 
//		 uint8_t   ContactorStat;         // ֱ���Ӵ���
	   	
}SwitchStatus;
extern SwitchStatus SwitchStat;

extern void BMSMain(void);

#endif

