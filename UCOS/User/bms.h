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

#define CAUSE_USER_NORMAL_STOP 										0x00//�û�����ֹͣ
#define CAUSE_WAIT_INSERTGUN_TIMEOUT							0x01//�ȴ���ǹ��ʱ
#define CAUSE_LOCK_GUN_FAILED											0x02//��ǹʧ��
#define CAUSE_K1K2_ADHESION_FAULT									0x03//�̵���ճ������
#define CAUSE_K1K2_CLOSE_FAULT										0x04//�̵����ܶ�����
#define CAUSE_K1K2_OUTSIDE_VOL_GREATER_THAN_10V		0x05//��Ե���ǰK1K2����ѹ����10V
#define CAUSE_CHARGEMODULE_OUTPUT_FAULT						0x06//���ģ���������
#define CAUSE_INSULATION_DETECT_FAULT							0x07//��Ե����쳣
#define CAUSE_BLEED_UNIT_FAULT										0x08//й�ŵ�·�쳣
#define CAUSE_BMS_PARA_CANNOT_FIT									0x09//�����������ʺ�
#define CAUSE_START_VOLTAGE_FAULT									0x0A//����ʱ��ѹ�쳣
#define CAUSE_BATTERY_READY_TO_NOREADY						0x0B//���׼��������Ϊδ����
#define CAUSE_SUSPEND_TIMEOUT											0x0C//���׮�������ͣ��ʱ
#define CAUSE_CC1_FAULT														0x0D//CC1�쳣
#define CAUSE_BMS_COMMUNICATE_TIMEOUT							0x0E//BMSͨ�ų�ʱ
#define CAUSE_SCRAMSTOP_FAULT											0x0F//��ͣ��������
#define CAUSE_DOOR_OPEN_FAULT											0x10//�Ž�����
#define CAUSE_GUNPORT_OVERTEMP										0x11//���ӿڹ���
#define CAUSE_OUPUTVOLTAGE_OVER_FAULT							0x12//ֱ�������ѹ��ѹ����
#define CAUSE_DEMANDVOL_FAULT											0x13//�����ѹ�쳣
#define CAUSE_BSM_SINGLEBATTERY_OVERVOL_FAULT			0x14//BSM�����е��嶯�����ص�ѹ����
#define CAUSE_BSM_SINGLEBATTERY_LESSVOL_FAULT			0x15//BSM�����е��嶯�����ص�ѹ����
#define CAUSE_BSM_SOC_OVER_FAULT									0x16//BSM������SOC����
#define CAUSE_BSM_SOC_LESS_FAULT									0x17//BSM������SOC����
#define CAUSE_BSM_SINGLEBATTERY_OVERCUR_FAULT			0x18//BSM�����е��嶯�����ص�������
#define CAUSE_BSM_TEMP_OVER_FAULT									0x19//BSM�����ж��������¶ȹ���
#define CAUSE_BSM_INSULATION_FAULT								0x1A//BSM�����ж������ؾ�Ե״̬�쳣
#define CAUSE_BSM_OUTPUTCONNECTER_FAULT						0x1B//BSM�����ж����������������������״̬�쳣
#define CAUSE_BST_NORMAL_REACHSOC									0x1C//BST�����дﵽ�������SOCĿ��ֵ
#define CAUSE_BST_NORMAL_REACHTOTALVOL						0x1D//BST�����дﵽ�ܵ�ѹ���趨ֵ
#define CAUSE_BST_NORMAL_REACHSINGLEVOL						0x1E//BST�����дﵽ�����ѹ���趨ֵ
#define CAUSE_BST_FAULT_INSULATION								0x1F//BST�����о�Ե����
#define CAUSE_BST_FAULT_OUTPUTCONNECTER_OVERTEMP	0x20//BST������������������¹���
#define CAUSE_BST_FAULT_ELEMENT_OVERTEMP					0x21//BST������BMSԪ�����������������
#define CAUSE_BST_FAULT_OUTPUTCONNECTER						0x22//BST�����г������������
#define CAUSE_BST_FAULT_BATTERYOVERTEMP						0x23//BST�����е�����¶ȹ��߹���
#define CAUSE_BST_FAULT_RELAY											0x24//BST�����и�ѹ�̵�������
#define CAUSE_BST_FAULT_CHECKPOINT2								0x25//BST�����м���2��ѹ������
#define CAUSE_BST_FAULT_OTHER											0x26//BST��������������
#define CAUSE_BST_ERROR_CUR												0x27//BST�����е�������
#define CAUSE_BST_ERROR_VOL												0x28//BST�����е�ѹ����
#define CAUSE_CP_FAULT														0x29//CP�쳣
#define CAUSE_CC_FAULT														0x2A//CC�쳣
#define CAUSE_GET_SOURCE_FAILED                   0x2B//�����Դ����ʧ��
#define CAUSE_DC_OVERCUR_FAULT                    0x2C//ֱ���������
#define CAUSE_AC_OVERVOL_FAULT                    0x2D//���������ѹ
#define CAUSE_AC_LESSVOL_FAULT                    0x2E//�������Ƿѹ
#define CAUSE_AC_OVERCUR_FAULT                    0x2F//�����������
#define CAUSE_AC_LESSCUR_FAULT                    0x30//�������Ƿ��
#define CAUSE_MONEY_FAULT                         0x31//�˻�����
#define CAUSE_MODULE_OVERVOL_FAULT                0x32//���ģ�������ѹ
#define CAUSE_MODULE_LESSVOL_FAULT                0x33//���ģ������Ƿѹ
#define CAUSE_ELM_FAULT                           0x34//������
#define CAUSE_PAUSE_TIMES_FAULT                   0x35//����г����ͣ��������
#define CAUSE_DC_LESSCUR_FAULT                    0x36//ֱ�����Ƿ��
#define CAUSE_CHG_COMPLETED                       0x37//��������

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
	   uint8_t   StopCause;		 		     //ֹͣ����	 
	   uint32_t  StopReason;		       //ֹͣԭ��
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

