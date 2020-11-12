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

#define CAUSE_USER_NORMAL_STOP 										0x00//用户正常停止
#define CAUSE_WAIT_INSERTGUN_TIMEOUT							0x01//等待插枪超时
#define CAUSE_LOCK_GUN_FAILED											0x02//锁枪失败
#define CAUSE_K1K2_ADHESION_FAULT									0x03//继电器粘连故障
#define CAUSE_K1K2_CLOSE_FAULT										0x04//继电器拒动故障
#define CAUSE_K1K2_OUTSIDE_VOL_GREATER_THAN_10V		0x05//绝缘检测前K1K2外侧电压大于10V
#define CAUSE_CHARGEMODULE_OUTPUT_FAULT						0x06//充电模块输出故障
#define CAUSE_INSULATION_DETECT_FAULT							0x07//绝缘检测异常
#define CAUSE_BLEED_UNIT_FAULT										0x08//泄放电路异常
#define CAUSE_BMS_PARA_CANNOT_FIT									0x09//车辆参数不适合
#define CAUSE_START_VOLTAGE_FAULT									0x0A//启动时电压异常
#define CAUSE_BATTERY_READY_TO_NOREADY						0x0B//电池准备就绪变为未就绪
#define CAUSE_SUSPEND_TIMEOUT											0x0C//充电桩充电中暂停超时
#define CAUSE_CC1_FAULT														0x0D//CC1异常
#define CAUSE_BMS_COMMUNICATE_TIMEOUT							0x0E//BMS通信超时
#define CAUSE_SCRAMSTOP_FAULT											0x0F//急停动作故障
#define CAUSE_DOOR_OPEN_FAULT											0x10//门禁故障
#define CAUSE_GUNPORT_OVERTEMP										0x11//充电接口过温
#define CAUSE_OUPUTVOLTAGE_OVER_FAULT							0x12//直流输出电压过压故障
#define CAUSE_DEMANDVOL_FAULT											0x13//需求电压异常
#define CAUSE_BSM_SINGLEBATTERY_OVERVOL_FAULT			0x14//BSM报文中单体动力蓄电池电压过高
#define CAUSE_BSM_SINGLEBATTERY_LESSVOL_FAULT			0x15//BSM报文中单体动力蓄电池电压过低
#define CAUSE_BSM_SOC_OVER_FAULT									0x16//BSM报文中SOC过高
#define CAUSE_BSM_SOC_LESS_FAULT									0x17//BSM报文中SOC过低
#define CAUSE_BSM_SINGLEBATTERY_OVERCUR_FAULT			0x18//BSM报文中单体动力蓄电池电流过流
#define CAUSE_BSM_TEMP_OVER_FAULT									0x19//BSM报文中动力蓄电池温度过高
#define CAUSE_BSM_INSULATION_FAULT								0x1A//BSM报文中动力蓄电池绝缘状态异常
#define CAUSE_BSM_OUTPUTCONNECTER_FAULT						0x1B//BSM报文中动力蓄电池组输出连接器连接状态异常
#define CAUSE_BST_NORMAL_REACHSOC									0x1C//BST报文中达到所需求的SOC目标值
#define CAUSE_BST_NORMAL_REACHTOTALVOL						0x1D//BST报文中达到总电压的设定值
#define CAUSE_BST_NORMAL_REACHSINGLEVOL						0x1E//BST报文中达到单体电压的设定值
#define CAUSE_BST_FAULT_INSULATION								0x1F//BST报文中绝缘故障
#define CAUSE_BST_FAULT_OUTPUTCONNECTER_OVERTEMP	0x20//BST报文中输出连接器过温故障
#define CAUSE_BST_FAULT_ELEMENT_OVERTEMP					0x21//BST报文中BMS元件、输出连接器过温
#define CAUSE_BST_FAULT_OUTPUTCONNECTER						0x22//BST报文中充电连接器故障
#define CAUSE_BST_FAULT_BATTERYOVERTEMP						0x23//BST报文中电池组温度过高故障
#define CAUSE_BST_FAULT_RELAY											0x24//BST报文中高压继电器故障
#define CAUSE_BST_FAULT_CHECKPOINT2								0x25//BST报文中检测点2电压检测故障
#define CAUSE_BST_FAULT_OTHER											0x26//BST报文中其他故障
#define CAUSE_BST_ERROR_CUR												0x27//BST报文中电流过大
#define CAUSE_BST_ERROR_VOL												0x28//BST报文中电压过大
#define CAUSE_CP_FAULT														0x29//CP异常
#define CAUSE_CC_FAULT														0x2A//CC异常
#define CAUSE_GET_SOURCE_FAILED                   0x2B//充电资源申请失败
#define CAUSE_DC_OVERCUR_FAULT                    0x2C//直流输出过流
#define CAUSE_AC_OVERVOL_FAULT                    0x2D//交流输出过压
#define CAUSE_AC_LESSVOL_FAULT                    0x2E//交流输出欠压
#define CAUSE_AC_OVERCUR_FAULT                    0x2F//交流输出过流
#define CAUSE_AC_LESSCUR_FAULT                    0x30//交流输出欠流
#define CAUSE_MONEY_FAULT                         0x31//账户余额不足
#define CAUSE_MODULE_OVERVOL_FAULT                0x32//充电模块输入过压
#define CAUSE_MODULE_LESSVOL_FAULT                0x33//充电模块输如欠压
#define CAUSE_ELM_FAULT                           0x34//电表故障
#define CAUSE_PAUSE_TIMES_FAULT                   0x35//充电中充电暂停次数过多
#define CAUSE_DC_LESSCUR_FAULT                    0x36//直流输出欠流
#define CAUSE_CHG_COMPLETED                       0x37//充电已完成

typedef struct _MessageBMS
{   
	
	  uint8_t   BRMdatalen;           // BRM数据长度
	  uint8_t   BRMPackCount;         // BRM数据长度
	  uint16_t  BRMPNG;               // BRM数据长度	
	  uint8_t   CFGdatalen;           // CFG数据长度
	  uint8_t   CFGPackCount;         // CFG数据长度
	  uint16_t  CFGPNG;               // CFG数据长度			
	  uint8_t   BCSdatalen;           // BCS数据长度
	  uint8_t   BCSPackCount;         // BCS数据长度
	  uint16_t  BCSPNG;               // BCS数据长度		
//握手参数
    uint8_t   BHMflag;	
    uint8_t   BRMflag;	
	  uint16_t  SoftVersion;          // 版本号	
		uint8_t   BatteryType;          // 电池类型
    uint16_t  RatedBatteryVolume;   // 额定电池容量
    uint16_t  RatedBatteryVoltage;  // 额定电池电压
    uint16_t  RatedBatteryEnergy;  // 额定电池电压	
//配置参数
    uint8_t   BCPflag;		
	  uint8_t   SOC;                  // SOC
    uint16_t  MAXVoltage;           // 最高允许电压
	  uint16_t  MAXCurrent;	          // 最高允许电流
	  uint16_t  BatteryVoltage;       // 电池电压		
//需求参数	
		uint8_t   BROflag;              //BMS准备就绪 0=未收到BRO，1=收到收到BRO=0x00，2=收到BRO=0xAA
    uint16_t  RequestVoltage;       // 需求电压
	  uint16_t  RequestCurrent;       // 需求电流
		uint8_t   RequestChargeMode;    // 需求充电模式 
    uint8_t   BCLflag;              // 接收到BCL标志
		uint8_t   BCL1flag;             // 首次接收到BCL标志
		uint8_t   BCS1flag;             // 首次接收到BCS标志
    uint8_t   BCSflag;		          // 接收BCS标志
    uint8_t   BCSdataflag;					
//车状态参数		
    uint8_t   MAXSingleVoltageNO;	  // 最高单体电压编号
    uint8_t   MAXBatteryTemp;	      // 最高电池温度
    uint8_t   MAXBatteryTempNO;	    // 最高电池温度编号		
    uint8_t   MINBatteryTemp;	      // 最低电池温度
    uint8_t   MINBatteryTempNO;	    // 最低电池温度编号
    uint8_t   SingleVoltageOHOL;    // 单体电压过高过低
    uint8_t   SOCOHOL;              // SOC过高或者过低
    uint8_t   BatteryOC;            // 电池充电过流
    uint8_t   BatteryTempOH;        // 电池充电过温
		uint8_t   BatteryInsuFlag;      // 电池绝缘状态
		uint8_t   BatteryCnetFlag;		  // 连接器状态
		uint8_t   BatteryChgAlow;       // 充电允许
		uint16_t  ChargeSuspendTime;    // 充电暂停时间
//测量数据
		uint16_t  BCSdetVoltage;	      // 汽车测量充电电压
	  uint16_t  BCSdetCurrent;        // 汽车测量充电电流		
		uint16_t  MAXSingleVoltage;	    // 最高允许单体电压
	  uint16_t  MINSingleVoltage;		  // 最低允许单体电压
	  uint16_t  RemainTime;		        // 剩余时间估算
    uint16_t  SingleVoltage;        // 单体电压
	  uint8_t   MAXSingleVoltageTemp; // 最高允许单体温度
	  uint8_t   MINSingleVoltageTemp;	// 最低允许单体温度
	  uint8_t   SingleVoltageTemp;    // 单体温度
		uint8_t   VIN[17];		          // 车辆识别码 ASCII码
	  uint8_t   CS;                   // 校验位
//停止数据原因	
    uint8_t   BSTflag;
    uint8_t   BSDflag;				
}BMSMsg;

extern BMSMsg BMSMessage;

typedef struct _MessageCharger
{	
	   uint8_t   ChargeStage;          // 充电阶段
     uint16_t  ChargeVoltage;                                         
     uint16_t  ChargeCurrent; 
	   uint32_t  ChargerEnergy;
	   uint16_t  ChargedTime;
     uint16_t  InsuVoltage;           // 绝缘检测电压
	   uint16_t  InsuCurrent;	          // 绝缘检测电流	
     uint16_t  MAXVoltage;            // 最高允许电压
     uint16_t  MINVoltage;            // 最高允许电压	
	   uint16_t  MAXCurrent;	          // 最高允许电流
	   uint16_t  MINCurrent;	          // 最高允许电流	
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
		 uint16_t  Stopcnt;              //超时停止
		 uint8_t   SE12SwitchFlag;       //辅助电源吸合标志
	   uint8_t   DCSwitchFlag;         //直流接触器吸合标志
		 uint8_t   StartCompleteflag;    //启动成功标志
     uint8_t   StopCompleteflag;     //停止成功标志
	   uint8_t   PreCharge;		 		     //预充标志
	   uint8_t   StopCause;		 		     //停止起因	 
	   uint32_t  StopReason;		       //停止原因
}ChargeMsg;
extern ChargeMsg ChargerMsg;

typedef struct _SwitchStatus
{		
	   uint8_t   EMGStat;               // 急停
	   uint8_t   DoorStat;              // 门禁
	   uint8_t   ELockerStat;           // 电磁锁 
//		 uint8_t   ContactorStat;         // 直流接触器
	   	
}SwitchStatus;
extern SwitchStatus SwitchStat;

extern void BMSMain(void);

#endif

