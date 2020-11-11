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
	   uint32_t  StopReason;		
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

