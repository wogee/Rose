/****************************************Copyright (c)****************************************************
**                                     Tomorn  Co.,LTD.
**                                     
**                                   http://www.tomorn.cn
**                                       wujikun
文件名称：BMS.C
功    能：与车端BMS通讯
编写时间：2019.10.18
编 写 人：
注    意：
                   0xXXXXF456 为充电机到BMS
                   0xXXXX56F4 为BMS到充电机
1 握手
         充电机(CRM)     ----->BMS       (00 A8 00 00 00 00 00 00  )
                                         byte0：00 请求BMS握手，如果BMS有回应变为AA。
                                         byte1：A8充电机编号，我们公司默认为A8
                                         byte2-7:6个字节为充电机充电站所在的编号，可选信息。

         BMS(RTS)        ----->充电机    (10 31 00 06 ff 00 02 00 )     BMS发送RTS报文(ID:1CEC56F4)，通知充电机准备发送多少包数据
                                                                        byte0: 10 控制字符，表示通知我要发多包
                                                                        byte1: 0x29=49 我要发49字节数据
                                                                        byte3: 07 表示多包数据总共7帧
                                                                        byte5-7: 0x00 02 00=512 PGN为512代表BMS和车辆识别报文

         充电机(CTS)     ----->BMS       (11 06 01 FF FF 00 02 00 )     当充电机收到BMS发送的RTS报文后，作出应答信号，回复CTS给BMS
                                                                        byte0：11 控制字表示充电机收到了多包协议请求
                                                                        byte1: 06 多包数据为6帧
                                                                        byte2: 01 下一个要接收数据的包头
                                                                        byte5-7:00 02 00 PGN为512代表BMS和车辆识别报文
                                                                        
         BMS(DT)         ----->充电机    （7包数据）                    当BMS接收到充电机的应答报文CTS后，开始建立连接发送数据DT（数据长度为41Byte，共分为6包
                                                                        8字节数据其实就7字节有用，总共41字节数据
                                                                        01包数据为byte1-7对应数据0-6,
                                                                        02包数据为byte0-7对应数据7-13，以此类推后面的
                                         0x1ceb56f4 01 01 01 00 06 bc 02 fa
                                         0x1ceb56f4 02 0b ff ff ff ff ff ff
				                                                                数据0-2:01 01 00 BMS通讯协议号V1.1
                                                                        数据3: 电池类型，01H：铅酸电池；02H：镍氢电池；03H：磷酸铁锂电池；04H：锰酸锂电池；05H：钴酸电池；06H：三元材料电池；07H：聚合物锂离子电池；08H：钛酸锂电池；FFH：其它电池
                                                                        数据4-5：bc 02:电池容量
                                                                        02bc=700*0.1=70A.h
                                                                        数据6-7：fa0b电池额定电压
                                                                        0bfa=3058*0.1=305.8V
                                                                        数据8-40是可选数据，没有默认为FF
                                                                        
																电池发充电参数报文																				
			   充电机(EM)      ----->BMS	      (13 29 00 06 ff 00 02 00)     当充电机接受到了接收完BMS发送到数据报文DT后，回复CM给BMS用于消息结束 

         充电机(CRM)     ----->BMS	      (aa A8 00 00 00 00 00 00)     发送握手成功指令  
				 
				 
2 参数配置

         BMS(RTS)         ----->充电机     (10 0d 00 02 ff 00 06 00)    首先BMS发送RTS给充电机 通知充电机准备发送多少包数据
				
				充电机(CTS)      ----->BMS	      (11 02 01 FF FF 00 06 00)    当充电机收到BMS发送的RTS报文后，作出应答信号，回复CTS给BMS   
				
				BMS(DT)          ----->充电机     当BMS接收到充电机的应答报文CTS后，开始建立连接发送数据DT（数据长度为13Byte，共分为2包)         相当于 0x80656f4
				                                   动力蓄电池充电参数报文
																			     第 1~2   字节	单体动力蓄电池最高允许充电电压
																				   第 3~4   字节	最高允许充电电流
																				   第 5~6   字节	蓄电池标称总能量
																				   第 7~8   字节	最高允许充电总电压
																				   第 9     字节	最高允许温度
																				   第 10~11 字节	整车动力蓄电池荷电状态
																				   第 12    字节	整车动力蓄电池总电压
															                     0x1cec56f4 10 0d 00 02 ff 00 06 00
                                                   0x1cecf456 11 02 01 ff ff 00 06 00
			                                                            10 BMS请求发 2包13字节数据 PNG为000600=1536.
                                                                  11 充电机收到BMS多包请求，2包数据，下一包数据包头为01，PNG为1536
                                                  0x1ceb56f401 93 01 1c 0c df 00 34
                                                  0x1ceb56f402 0d 62 e8 03 b8 0d ff
                                                                  数据0-1: 9301 最高单体允许电压0193=403*0.01=4.03V
                                                                  数据2-3:1c0c 最大允许充电电压0c1c=3100*0.1=310，电流为400-310=90A，电流有-400A偏移量。
                                                                  数据4-5：df00 电池能量0x00df=223*0.1=22.3KW.h
                                                                  数据6-7:340d 最高允许充电总电压0x0d34=3380*0.1=338V
                                                                  数据8:62最高允许温度0x62=98-40=58度，温度有40度偏移。
                                                                  数据9-10：e803 电池SOC值0x03e8=1000*0.1=100%。
                                                                  数据11-12：b80d 电池总压0x0db8=3512*0.1=351.2V								   

        充电机(TPCM_EM) ----->BMS	       (13 0d 00 02 ff 00 06 00)       当充电机接受到了接收完BMS发送到数据报文DT后，回复CM给BMS用于消息结束应答
				
				充电机(CTS)     ----->BMS        (00 00 00 00 00 00 00  )	      充电机发送时间同步信息CTS给BMS
				                                 
                                                                  byte0：BCD码秒 byte1：BCD码分
                                                                  byte2：BCD码时 byte3：BCD码日
                                                                  byte4：BCD码月 byte5：BCD码年
                                                                  注：　BCD码为十进制 59=59秒               
		
				充电机(CML)     ----->BMS        (68 10 d0 07 b8 0b)             充电机最大输出级别CML给BMS  英可瑞 300（012C）---750(02EE)V  10A电流
                                                     0x1808f456 4c 1d d0 07 d0 07 00 00
				                                                        byte0-1:4c1d 最大输出电压1d4c=7491=7491*0.1=749.1V.
                                                                byte 2-3：d007最低输出电压200V
                                                                byte4-5：d007最大输出电流400-200=200A
				
				BMS(BRO)        ----->充电机     (aa               )             BMS发送电池充电准备就绪状态BRO给充电机
				                                                       aa 准备好了 00未准备好
				
        充电机(CRO)     ----->BMS        (aa               )             充电机接收到BMS发送到BRO信息后回应充电机输出准备就绪状态CRO        
				                                                       aa 准备好了 00未准备好
				
3  充电阶段

       BMS(BCL)        ----->充电机      (E2 18 76 0C 02 )               BMS发送电池充电级别BCL给充电机（ID：181056F4）. Byte1和 Byte2是电压，Byte 3和Byte4是电流
                                                         0x181056f4 98 0d 10 0e 01 00 00 00
                                                                         byte0-1:980D需求电压0d98=348V
                                                                         byte2-3:100e需求电流0e10=3600*0.1=360-400=40A
                                                                         byte4：01充电模式 01恒压，02恒流

			 BMS(BCS)   ----->充电机      (10 09 00 02 ff 00 aa 00)       首先BMS发送BCS报文，通知充电机准备发送多少包数据
			                                             0x1cec56f4 10 09 00 02 ff 00 11 00
			                                                          PNG 001100 =4352 电池充电总状态报文   
			
       充电机    ------>BMS	  		  (11 02 01 ff ff 00 11 00)	     当充电机收到BMS发送的BCS报文后，作出应答信号，回复给BMS  
			 
			 BMS(DT)   ----->充电机       （数据长度为9Byte，共分为2包)     当BMS接收到充电机的应答报文CTS后，开始建立连接发送数据DT  BMS发送电池充电总状态BCS给充电机
			                                    0x1ceb56f4 01 77 0e 96 0f 7e c1 42
                                                0x1ceb56f4 02 58 02 ff ff ff ff ff
                                                           数据0-1：770e充电电压检测0e77=370.3V
                                                           数据2-3：960f充电电流检测0f96=3990*0.1-400=0.1A  
                                                           数据4-5:7ec1 最高单体电压及组号，最高单体电压0-11位，0x17e=382*0.01=3.82,单体组号为12-15位0X07=7,第7组电池单体
                                                           数据6:  42 当前电池SOC=0x42=66%
                                                           数据7-8：5802剩余充电时间0x0258=600min，单位分钟
                                                           
                                                                        BMS电池充电总状态     1--2 充电电压测量值（V）  3--4 充电电流测量值（A）  5--6 最高单体动力蓄电池电压及其组号
                                                                                              7 当前荷电状态SOC（%） 8--9  估算剩余充电时间（min）
			 充电机      ----->BMS	  	   (13 09 00 02 ff ff ff ff ff)    当充电机接受到了接收完BMS发送到数据报文DT后，回复给BMS用于消息结束应答

			 充电机(CCS) ----->BMS	       (00 00 a0 0f 000 00)            充电机发送充电状态CCS给BMS
			                                        0x1812f456 b8 0d a0 0f 00 00 00 00
			                                            byte0-1：b80d电压输出值0x0db8=3512=351.2V
                                                        byte2-3：a00f电流输出值0x0fa0=4000=0A
                                                        byte4-5:0000累计充电时间，单位分钟
       BMS(BSM)   ----->充电机                                           
                                                    0x181356f4 4e 4e 91 4d 83 04 10 00
                                                        byte0：4e最高编号0x4e=78号
                                                        byte1:4e最高单体温度0x4e=78-50=28度
                                                        byte2:91最高温度编号0x91=145号
                                                        byte3:4d最低温度0x4d=77-50=27度
                                                        byte4：83最低电池编号 0x83=131号
                                                                                            注：这里温度偏移量是-50度
                                                        byte5-6:0410电池状态信息，0X1004=0B00010000 0000 0100数据2位一个信息
                                                                bit 0-1：0B00电池总压状态 00整正常，01过高，10过低；
                                                                bit 2-3:0B01电池SOC 状态00正常01过高10过低
                                                                bit 4-5: 0B00充电电流过流00正常01过流10不可信
                                                                bit 6-7:0B00电池温度00正常01过高10过低
                                                                bit 8-9:0B00 绝缘状态00正常01不正常10不可信
                                                                bit 10-11:0B00 输出连接器状态00正常01不正常10不可信
                                                                bit 8-9:0B01 充电允许00禁止01允许



                                                         
			                                                             BMS通过数据传输协议发送单体电压BMV给充电机（具体步骤和握手阶段的数据传输协议一样）可选。
                                                                         BMS发送蓄电池组温度BMT给充电机.（具体步骤和握手阶段的数据传输协议一样）  可选。
		
              BMS(BST)    ----->充电机
                                        0x101956f4 10 00 00 00 00 00 00 00
                                               byte0:10 BMS终止充电原因 0B0001 0000
                                               bite0-1：所需SOC值 00未达到 01达到10不可信
                                               bite2-3：设定电压值 00 未达到01达到10不可信
                                               bite4-5：设定单体电压值 00 未达到01达到10不可信
                                                   bit:1-2：0x00=0B0000 0000 0000 0000 　BMS终止充电故障原因 bite0-1：绝缘 bite2-3：输出连接器过温bite4-5：BMS元件输出连接器过温 
                                               bite6-7：充电连接器故障
                                               bite8-9：电池组温度过高bite10-11：其他故障 00正常，01故障，10不可信
                                              

              充电机(CST) ----->BMS	    0x101af456 00 00 00 00 00 00 00 00

                                             BYTE0 充电机中止充电原因
                                             BYTE1-2 充电机中止充电故障原因
                                             BYTE3 充电机中止充电错误原因
                                             1、充电机中止充电原因：
                                                a)1~2位：达到充电机设定的条件中止（00：正常，01：达到设定条件中止，10：不可信状态）
                                                b)3~4位：人工中止（00：正常，01：人工中止，10：不可信状态）
                                                c)5~6位：故障中止（00：正常，01：故障中止，10：不可信状态）
                                             2、充电机中止充电故障原因：
                                                a)1~2位：充电机过温故障（00：温度正常，01：充电机过温，10：不可信状态）
                                                b)3~4位：充电连接器故障（00：连机器正常，01：故障，10：不可信状态）
                                                c)5~6位：充电机内部过温故障（00：内部温度正常，01：内部过温，10：不可信）
                                                d)7~8位：所需电量不能传送（00：传送正常，01：不能传送，10：不可信）
                                                e)9~10位：充电机急停故障（00：正常，01：急停，10：不可信状态）
                                                f)11~12位：其它故障（00：正常，01：故障，10：不可信状态）
                                             3、充电机中止充电错误原因：
                                                a)1~2位：电流不匹配（00：电流匹配，01：电流不匹配，10：不可信状态）
                                                b)3~4位：电压异常（00：正常，01：异常，10：不可信状态）
																								
																								
4  结束阶段																							
              BMS(BSD)   ----->充电机               
                                         0x181C56F4
                                           BYTE0 中止时SOC 值（比例：1%，偏移量：0）
                                           BYTE1 动力蓄电池单体最低电压（比例：0.01，偏移量：0）
                                           BYTE2
                                           BYTE3 动力蓄电池单体最高电压（比例：0.01，偏移量：0）
                                           BYTE4
                                           BYTE5 动力蓄电池最低温度（比例：1，偏移量：-50）
                                           BYTE6 动力蓄电池最高温度（比例：1，偏移量：-50）

              充电机(CSD) ----->BMS
                                          0x181DF456
                                              BYTE0 累计充电时间（比例：1min，偏移量：0，范围：0~600）
                                              BYTE1
                                              BYTE2 累计输出能量（比例：0.1kw·h，偏移量：0，范围：0~1000）
                                              BYTE3
                                              BYTE4 充电机编号

5  错误报文
          BMS(BEM)   ----->充电机
         
                          ID:081E56F4 (PGN=7680)

                        BYTE0 Bit0-Bit1 接受SPN2560=0X00 充电机辨识报文超时（00：正常，01：超时，10：不可信状态）
                              Bit2-Bit3 接受SPN2560=0XAA 充电机辨识报文超时（00：正常，01：超时，10：不可信状态）
                        BYTE1 Bit0-Bit1 接受充电机的时间同步和充电机最大能力报文超时（00：正常，01：超时，10：不可信状态）
                              Bit2-Bit3 接受充电机完成充电准备报文超时（00：正常，01：超时，10：不可信状态）
                        BYTE2 Bit0-Bit1 接受充电机充电状态报文超时（00：正常，01：超时，10：不可信状态）
                              Bit2-Bit3 接受充电机中止报文超时（00：正常，01：超时，10：不可信状态）
                        BYTE3 Bit0-Bit1 接受充电机充电统计报文超时（00：正常，01：超时，10：不可信状态）

         充电机(CSD) ----->BMS 
                         ID:081FF456 (PGN=7936)
                              BYTE0 Bit0-Bit1 接受BMS 和车辆的辨识报文超时（00：正常，01：超时，10：不可信状态）
                              BYTE1 Bit0-Bit1 接受电池充电参数报文超时（00：正常，01：超时，10：不可信状态）
                              Bit2-Bit3 接受BMS 完成充电前准备报文超时（00：正常，01：超时，10：不可信状态）
                              BYTE2 Bit0-Bit1 接受电池充电总状态报文超时（00：正常，01：超时，10：不可信状态）
                              Bit2-Bit3 接受电池充电需求报文超时（00：正常，01：超时，10：不可信状态）
                              Bit4-Bit5 接受BMS 中止充电报文超时（00：正常，01：超时，10：不可信状态）
                              BYTE3 Bit0-Bit1 接受BMS 充电统计报文超时（00：正常，01：超时，10：不可信状态）

	
**********************************************************************************************************************************/
#include <bms.h>
#include <insulation.h>
#include <adc.h>

unsigned char BatterMessage[49];         //电池参数数据包 
unsigned char CFGMessage[13];            //配置参数数据包 
unsigned char BCSMessage[9];             //充电测量数据包

uint8_t InsulationFlag  ;   //  1，开始做绝缘检测  2，绝缘检测完成 3，绝缘检测的整个流程走完。
uint8_t OutVoltageDetFlag;  //  1，开始检测电池电压  2，电池电压检测通过   3，电池电压检测不通过

BMSMsg BMSMessage;
ChargeMsg ChargerMsg;

static void ChargerMsgInit(void);
static void BMS_CHM(void);
static void BMS_CRM(uint8_t data);
static void BMS_DataAnswerHead(uint8_t packlen,uint16_t png);
static void BMS_DataAnswerEnd(uint8_t datalen,uint16_t png);
static void BMS_CTS(); 
static void BMS_CML(void);
static void BMS_CRO(uint8_t data);
static void BMS_CCS(void);
static void BMS_CST(uint32_t  flag);
static void BMS_CSD(void);
static void BMS_CEM(uint32_t  err);
static void BMS_RECData_Pro(void);

void ChargerMsgInit(void)
{
	 ChargerMsg.ChargeStage=0; //阶段清零
   InsulationFlag    = 0;    //绝缘检测状态清零
   OutVoltageDetFlag = 0;	   //外部电压检测清零
	 ChargerMsg.PreCharge=0;   //预充标识	
	 ChargerMsg.CHMcnt=0;      //计数器清零
	 ChargerMsg.CRMcnt=0;
	 ChargerMsg.CMLcnt=0;
	 ChargerMsg.CTScnt=0;
	 ChargerMsg.CROcnt=0;
	 ChargerMsg.BCLcnt=0;
	 ChargerMsg.BCScnt=0;	
	 ChargerMsg.CCScnt=0;
	 ChargerMsg.CSTcnt=0;	
	 ChargerMsg.CEMcnt=0;	
	 ChargerMsg.MAXVoltage=7500;
	 ChargerMsg.MINVoltage=2000;
	 ChargerMsg.MAXCurrent=2500;
   ChargerMsg.MINCurrent=0;		
	 ChargerMsg.ChargedTime=0;       //时间清零
	 ChargerMsg.StopReason=0;        //充电机停止原因清零
	 ChargerMsg.StartCompleteflag=0;  //启动成功标志
   ChargerMsg.StopCompleteflag=0;  //停止成功标志	
   ChargerMsg.SE12SwitchFlag=0;
	 ChargerMsg.DCSwitchFlag=0;
	 BMSMessage.BHMflag=0;	   //收到BHM报文	 
	 BMSMessage.BRMflag=0;	   //收到BRM报文
	 BMSMessage.BCPflag=0;	   //收到BCP报文	 
	 BMSMessage.BROflag=0;	   //收到BRO就绪报文标志
	 BMSMessage.BCLflag=0;     //收到BCL报文
	 BMSMessage.BCL1flag=0;    //首次收到BCL报文	 
	 BMSMessage.BCSflag=0;	   //收到BCS报文
	 BMSMessage.BCS1flag=0;	   //首次收到BCS报文		 
	 BMSMessage.ChargeSuspendTime=0;  //充电中暂停时间清零
}

void ChargeStart(void)
{
	  ChargerMsgInit();	
}

void ChargeStop(void)
{
		ChargerMsg.StopCompleteflag=1;  //停止成功标志
		ChargerMsg.ChargeStage=0;
}

void BMSMain (void)
{	
	  ChargerMsgInit();		
  while (1) 
 {							
    OSTimeDlyHMSM(0,0,0,1);	
	  if((ADstatus != ADC4V)&&(ChargerMsg.ChargeStage>=2))                                // CC异常状态处理
	 {
		 ChargerMsg.ChargeStage=8;
	 }
	 else if((ADstatus != ADC4V)&&(ChargerMsg.ChargeStage==1))                            // CC异常状态处理
	 {
	   ChargerMsg.ChargeStage=0;
	 	 //未插枪，做插枪提示
	 }		 
		BMS_RECData_Pro();                                                                 // 处理充电桩过来的数据 ，主要是被动处理函数 	 	 
	switch (ChargerMsg.ChargeStage)
	{
    case 1: 	
		    	ChargeStart();
			    LOCK_SWITCH_ON();
				  OSTimeDlyHMSM(0,0,0,100);
				  SE12V_SWITCH_ON();                                                           //吸合辅助电源
		      ChargerMsg.SE12SwitchFlag=1;
			    OSTimeDlyHMSM(0,0,0,100);
				  AC_SWITCH_ON();                                                              //吸合交流接触器	
					OSTimeDlyHMSM(0,0,1,0);
		      ChargerMsg.ChargeStage=2;
		     break;		
		case 2:	 	                                                                         //定期发送协议版本			
			   ChargerMsg.CHMcnt++;
		     if((ChargerMsg.CHMcnt%250)==0)                                                //电池充电总状态，250ms发送一次  
		     {       
				    BMS_CHM();
		     }		
				//BMS通讯超时 当CHM发送时间超过5秒时	判断通讯超时	
         if((ChargerMsg.CHMcnt>=8000)&&(BMSMessage.BHMflag==0))
					 {
					   ChargerMsg.ChargeStage=8;
					 }					
	       break; 								
	  case 3:				                                                                      //定期发送开始握手报文
	   		 ChargerMsg.CRMcnt++;			
         if(ChargerMsg.CRMcnt<5*1000)			
				 {
		       if(BMSMessage.BRMflag==0)
			    	{
							if((ChargerMsg.CRMcnt%250)==0)                                             //电池充电总状态，250ms发送一次  
							{       
								BMS_CRM(0x00);
							}
						}
					}
         else if(ChargerMsg.CRMcnt>=5*1000)	
						{
						  BMS_CEM(0xfdf0c0fc);                                                     // DN.1001 DN.1002 DN.1003 接收BMS辨识报文超时
							ChargerMsg.ChargeStage=9;
						}																		
					break;						
	 	 case 4:	
			 	    ChargerMsg.CRMcnt++;
          	if(ChargerMsg.CRMcnt<5*1000)
            {							
								 if((ChargerMsg.CRMcnt%250)==0)                                        //电池充电总状态，250ms发送一次  
								{       
									BMS_CRM(0xaa);
								}
						}
						 if(ChargerMsg.CRMcnt>=5*1000)	                                           // DN.1004 DN.2001 DN.2002接收BMS配置参数超时
						{
									BMS_CEM(0xfcf1c0fc); 
					        ChargerMsg.ChargeStage = 9;							
						}			     
					break;						
		 case 5:				                                                                   //定期发送最大输出能力报文	
							ChargerMsg.CMLcnt++;
							ChargerMsg.CTScnt++;
		 					if(ChargerMsg.CTScnt<5*1000)
								{
					       if(BMSMessage.BCPflag==1)
						      {
							    	if((ChargerMsg.CMLcnt%250)==0)             
									   {       
									   	   BMS_CML();
									    }	
								    if((ChargerMsg.CTScnt%500)==0)            
								    	{       
									    	BMS_CTS();
									    }
								   }
								}
             else if	(ChargerMsg.CTScnt>=5*1000)	                                    //DN.2003 DN.2004 DN.2006 接收BMS完成充电准备超时               
							 {							
					          BMS_CEM(0xfcf4c0fc); 	
					          ChargerMsg.ChargeStage = 9;								 
							 }																						
							break;								 
		case 6:	 	                                                                                        // 定期发送握手状态报文
			      ChargerMsg.CROcnt++;	 			
					if(ChargerMsg.CROcnt<60*1000)	
					{								
               if((BMSMessage.BCL1flag==0)&&(BMSMessage.BCS1flag==0))                                  //BCL和BCS都没接收到时
							 {
									switch (OutVoltageDetFlag) 
									{
										 case 0:									 
														BMS_CRO(0x00);
                            OutVoltageDetFlag=1;													 												 											 												 
												 break;					
										 case 1:	
												if((ChargerMsg.CROcnt%250)==0)                                               
												 {									 
														BMS_CRO(0x00);
												 }	
												 break; 
										 case 2:
												if((ChargerMsg.CROcnt%250)==0)                                                //电池充电总状态，250ms发送一次  
												 {
                           if(BMSMessage.BROflag==2)	                                        //若一直为准备完成，则一直发CRO=0x00。     
													 {														 
															 BMS_CRO(0xaa);
															 ChargerMsg.ChargeStage=7;	
															 ChargerMsg.CROcnt=0;	
													 } 
													 else{														 
													     BMS_CRO(0x00);
													 }														 
													}							      
												 break;											
											case 3:
												 //检测汽车电压是否误差是否超过5%
												 break;											
											default:
													break;									
										}
							  	}																																					 
						 }	
					 else if(ChargerMsg.CROcnt>=60*1000)                                         //DN.2005 接收BMS完成充电准备超时    
						 {			
                  if(BMSMessage.BROflag!=2)	
									{										
							      BMS_CEM(0xfcf4c0fc);
					          ChargerMsg.ChargeStage = 9;										
									}										
							}								 				
          break;						
		case 7:                                                                               //充电阶段 
			      ChargerMsg.CROcnt++;	
			      ChargerMsg.CCScnt++;                                                      
		        ChargerMsg.BCLcnt++; 	
            ChargerMsg.BCScnt++; 		

		      if((BMSMessage.BCL1flag==0)||(BMSMessage.BCS1flag==0))                          //首次的BCL1和BCS1只要一个接收到，则进入
		      {
						if((ChargerMsg.CROcnt%250)==0)                                                //电池充电总状态，250ms发送一次  
				    {									 
					   	BMS_CRO(0xaa);	
						}
						 if(BMSMessage.BCS1flag==1)                                                   // DN.3002 DN.3004 接收到BCS未接收到BCL
						 {
							 if(ChargerMsg.BCLcnt>1000)
								{
									 BMS_CEM(0xfcf4c0fc);
					         ChargerMsg.ChargeStage = 9;									
								}
						  }
						 if(BMSMessage.BCL1flag==0)                                                   // DN.3001 DN.3003 接收到BCL未接收到BCS
						 {
							 if(ChargerMsg.BCScnt>5*1000)
								{															
									 BMS_CEM(0xfcf4c0fc);
				         	 ChargerMsg.ChargeStage = 9;									
								}	
				      }							
		      }					
					else if((BMSMessage.BCL1flag==1)&&(BMSMessage.BCS1flag==1))
		      {
						 if((BMSMessage.ChargeSuspendTime<(10*60))&&(BMSMessage.BatteryChgAlow	=0x10))   //充电暂停10分钟 可恢复
						 {
									if(ChargerMsg.BCLcnt>1000)                                                  // DN.3006 DN.3008 接收到BCL中断
									{
										 BMS_CEM(0xfcf4c0fc); 
										 ChargerMsg.ChargeStage = 9;
									}						
									if(ChargerMsg.BCScnt>5*1000)                                                // DN.3005 DN.3007 接收到BCS中断
									{															
										 BMS_CEM(0xfcf4c0fc); 	
										 ChargerMsg.ChargeStage = 9;							
									}
							}else if((BMSMessage.ChargeSuspendTime>(10*60))&&(BMSMessage.BatteryChgAlow	=0x00))//充电暂停超过10分钟，不可恢复
						 {
							 ChargerMsg.ChargeStage=8;
						 }					 
					}										
	       break;					
		case 8:                                                                          
					ChargerMsg.CSTcnt++;         
					ChargerMsg.BSDcnt++;			
				 if(BMSMessage.BSTflag==0)                                                         //主动停机
				 {
						if((ChargerMsg.CSTcnt%10)==0)                                                  //电池充电总状态，250ms发送一次  
						{ 			
							BMS_CST(ChargerMsg.StopReason);									
						}	
						if(ChargerMsg.CSTcnt>=5*1000) 
						{
							 BMS_CEM(0xfcf4c0fc); 	
							if(ChargerMsg.DCSwitchFlag==1)
								{	
									DC_SWITCH_OFF();
									LOCK_SWITCH_OFF();
									ChargerMsg.DCSwitchFlag=0;
									ChargerMsg.ChargeStage = 9;								
								}
						}
					}
				 else if(BMSMessage.BSTflag==1)                                                     //被动停机
				 {
					 	if((ChargerMsg.DCSwitchFlag==1)&&(ChargerMsg.ChargeCurrent<=50))                                      
						{						
							DC_SWITCH_OFF();
							ChargerMsg.DCSwitchFlag=0;
							ChargerMsg.ChargeStage=9;					
						 }
						if((ChargerMsg.CSTcnt%10)==0)                                                   //电池充电总状态，250ms发送一次  
						{ 			
							BMS_CST(ChargerMsg.StopReason);									
						}						 
						if(ChargerMsg.BSDcnt>=10*1000) 
						{
							BMS_CEM(0xfcf4c0fc); 	
							ChargerMsg.ChargeStage = 9;
						}				
					}											
				 break;						
		case 9:		
         if(ChargerMsg.DCSwitchFlag==1)
				 {
							DC_SWITCH_OFF();					
							ChargerMsg.DCSwitchFlag=0;
				 }
		      SE12V_SWITCH_OFF();                                                         //断开辅助电源
					OSTimeDlyHMSM(0,0,1,0);
				  LOCK_SWITCH_OFF();
	      	OSTimeDlyHMSM(0,0,1,0);			
					AC_SWITCH_OFF();                                                            //断开交流接触器
					ChargerMsg.ChargeStage=10;
	       break;		
    case 10:                                                                          //结束充电
		      ChargeStop();			
	       break;				
		default:
         break;			
	 }	
 }	
}
	
void BMS_CHM(void)    		          
{
   CANID=0x1826F456;
	 CAN_Data[0]=0x01;                
	 CAN_Data[1]=0x01;  
	 CAN_Data[2]=0x00;  	
	 WriteCAN0(3,1, CANID,CAN_Data);	 
}	

 void BMS_CRM(uint8_t data)    		          
{
   CANID=0x1801F456 ;
	 CAN_Data[0]=data;                
	 CAN_Data[1]=0x01;  
	 CAN_Data[2]=0x00;
	 CAN_Data[3]=0x00;                
	 CAN_Data[4]=0x00;  
	 CAN_Data[5]=0xff;
	 CAN_Data[6]=0xff;  
	 CAN_Data[7]=0xff;		
	 WriteCAN0(8,1, CANID,CAN_Data);	 
}	

 void BMS_CTS()    		          
{
   CANID=0x1807F456 ;
	 CAN_Data[0]=0xff;                
	 CAN_Data[1]=0xff;  
	 CAN_Data[2]=0xff;  	
	 CAN_Data[3]=0xff;                
	 CAN_Data[4]=0xff;  
	 CAN_Data[5]=0xff;  	
	 CAN_Data[6]=0xff;                
	 CAN_Data[7]=0xff;  	
	 WriteCAN0(8,1, CANID,CAN_Data);	 
}

 void BMS_CML(void)    		          
{
   CANID=0x1808F456 ;
	 CAN_Data[0]=ChargerMsg.MAXVoltage&0xff;                
	 CAN_Data[1]=(ChargerMsg.MAXVoltage>>8)&0xff;  
	 CAN_Data[2]=ChargerMsg.MINVoltage&0xff;  
	 CAN_Data[3]=(ChargerMsg.MINVoltage>>8)&0xff;                
	 CAN_Data[4]=(4000-ChargerMsg.MAXCurrent)&0xff;  
	 CAN_Data[5]=((4000-ChargerMsg.MAXCurrent)>>8)&0xff;  
	 CAN_Data[6]=(4000-ChargerMsg.MINCurrent)&0xff;    
	 CAN_Data[7]=((4000-ChargerMsg.MINCurrent)>>8)&0xff;  	
	 WriteCAN0(8,1, CANID,CAN_Data);		
}

void BMS_CRO(uint8_t data)	           	// 电池参数 动力蓄电池充电参数报文 aa
{
	 CANID=0x100Af456  ;
	if(data==00)
	{
	 CAN_Data[0]=0x00 ;
	}
	else
	{
	 CAN_Data[0]=0xaa ;
	}
	 WriteCAN0(1,1, CANID,CAN_Data);
}

void BMS_DataAnswerHead(uint8_t packlen,uint16_t png)    //充电机收到BMS发送的RTS报文后，作出应答信号，回复CTS给BMS  参数配置阶段 
{
	 CANID=0x1CECF456  ;               //11 02 01 FF FF 00 06 00 
	 CAN_Data[0]=0x11 ;
	 CAN_Data[1]=packlen ;
	 CAN_Data[2]=0x01 ;
	 CAN_Data[3]=0xff ;
	 CAN_Data[4]=0xff ;
	 CAN_Data[5]= png&0xff ;
	 CAN_Data[6]= png/0xff ;
	 CAN_Data[7]=0x00 ;  			
	 WriteCAN0(8,1, CANID,CAN_Data);
}

void BMS_DataAnswerEnd(uint8_t datalen,uint16_t png)    //充电机收到BMS发送的RTS报文后，作出应答信号，回复CTS给BMS  参数配置阶段 
{
	 CANID=0x1CECF456  ;               //11 02 01 FF FF 00 06 00 
	 CAN_Data[0]=0x13 ;
	 CAN_Data[1]=datalen ;
	 CAN_Data[2]=0x00 ;
	 CAN_Data[3]=0x02 ;
	 CAN_Data[4]=0xff ;
	 CAN_Data[5]= png&0xff ;
	 CAN_Data[6]= png/0xff ;
	 CAN_Data[7]=0x00 ;  			
	 WriteCAN0(8,1, CANID,CAN_Data);	
}

void BMS_CCS(void)		
{
	 CANID=0x1812f456 ;  
	 CAN_Data[0]=ChargerMsg.ChargeVoltage&0xff;
	 CAN_Data[1]=(ChargerMsg.ChargeVoltage>>8)&0xff;
	 CAN_Data[2]=(4000-ChargerMsg.ChargeCurrent)&0xff;
	 CAN_Data[3]=((4000-ChargerMsg.ChargeCurrent)>>8)&0xff;
	 CAN_Data[4]=ChargerMsg.ChargedTime&0xff;
	 CAN_Data[5]=(ChargerMsg.ChargedTime>>8)&0xff;
	 CAN_Data[6]=0xfd ; 			
	 WriteCAN0(7,1, CANID,CAN_Data);
}

void BMS_CST(uint32_t reason)		
{
	 CANID=0x101Af456 ;
	 CAN_Data[0]=reason&0xff;              //充电机中止充电原因
	 CAN_Data[1]=(reason>>8)&0xff;         //充电机中止充电故障原因
	 CAN_Data[2]=(reason>>16)&0xff; 
	 CAN_Data[3]=(reason>>24)&0xff;        //充电机中止充电错误原因
	 WriteCAN0(4,1, CANID,CAN_Data);
}
 
void BMS_CSD(void)		
{
	 CANID=0x181df456 ;
	 CAN_Data[0]=0x00 ;
	 CAN_Data[1]=0x00 ;
	 CAN_Data[2]=0x01 ;
	 CAN_Data[3]=0x99 ;
	 CAN_Data[4]=0x01 ;
	 CAN_Data[5]=0x3d ;
	 CAN_Data[6]=0x3e ;
	 WriteCAN0(8,1, CANID,CAN_Data);
}

void BMS_CEM(uint32_t err)	
{
	 CANID=0x081ff456 ;
	 CAN_Data[0]=(err>>24)&0xff ;
	 CAN_Data[1]=(err>>16)&0xff ;
	 CAN_Data[2]=(err>>8)&0xff ;
	 CAN_Data[3]=err&0xff ;
	 WriteCAN0(4,1, CANID,CAN_Data);
}	

void BHM_Analyse(void)	
{
		 BMSMessage.BHMflag=1;	                                 //收到BRM报文
   if(ChargerMsg.ChargeStage==2)
	 {
		   if(PRINT_STRING)
	     Print("%s\n", "chargestate 1 ,  handshake !"); 
       BMSMessage.MAXVoltage= MessageCAN0.DATAA&0xffff;			 //电压做绝缘检测使用
			 			 
			 /**  充电桩检测K1，K2外侧电压小于10V，正常了就进行绝缘检测 **/
			 		if(InsulationFlag==3)
					{
			 			 ChargerMsg.ChargeStage=3;
             ChargerMsg.CRMcnt++;								
						 InsulationFlag=0;
					}
		}   			 
}		

void DataPackCEC_Analyse(void)	
{		
     	switch (ChargerMsg.ChargeStage)
			{ 	
					case 3:	
							if(((MessageCAN0.DATAA&0xff)==0x10)&&((((MessageCAN0.DATAB)&0xff0000)>>8)==0x200))
							 {						
									BMSMessage.BRMflag= 1 ; 
									BMSMessage.BRMdatalen=(MessageCAN0.DATAA>>8)&0xff;
									BMSMessage.BRMPackCount=MessageCAN0.DATAA>>24;
									BMSMessage.BRMPNG=((MessageCAN0.DATAB)&0xff0000)>>8;								 
									BMS_DataAnswerHead(BMSMessage.BRMPackCount,BMSMessage.BRMPNG);
								 break;
							 }
					case 4:	
							 if(((MessageCAN0.DATAA&0xff)==0x10)&&((((MessageCAN0.DATAB)&0xff0000)>>8)==0x600))
								{
									BMSMessage.BCPflag=1;									
									BMSMessage.CFGdatalen=(MessageCAN0.DATAA>>8)&0xff;
									BMSMessage.CFGPackCount=MessageCAN0.DATAA>>24;
									BMSMessage.CFGPNG=((MessageCAN0.DATAB)&0xff0000)>>8;								 
									BMS_DataAnswerHead(BMSMessage.CFGPackCount,BMSMessage.CFGPNG);
								}					
								 break;
					
					case 6:					
					case 7:	
								if(((MessageCAN0.DATAA&0xff)==0x10)&&((((MessageCAN0.DATAB)&0xff0000)>>8)==0x1100))
								{
										ChargerMsg.StartCompleteflag=1;									
										BMSMessage.BCSflag=1;
										BMSMessage.BCS1flag=1;
										ChargerMsg.BCScnt = 0;
										BMSMessage.BCSdatalen=(MessageCAN0.DATAA>>8)&0xff;
										BMSMessage.BCSPackCount=MessageCAN0.DATAA>>24;
										BMSMessage.BCSPNG=((MessageCAN0.DATAB)&0xff0000)>>8;								 
										BMS_DataAnswerHead(BMSMessage.BCSPackCount,BMSMessage.BCSPNG);
								}
								else if(((MessageCAN0.DATAA&0xff)==0x10)&&((((MessageCAN0.DATAB)&0xff0000)>>8)==0x1500))
								{					
											BMSMessage.BCSdataflag=1;									
											BMSMessage.BCSdatalen=(MessageCAN0.DATAA>>8)&0xff;
											BMSMessage.BCSPackCount=MessageCAN0.DATAA>>24;
											BMSMessage.BCSPNG=((MessageCAN0.DATAB)&0xff0000)>>8;								 
											BMS_DataAnswerHead(BMSMessage.BCSPackCount,BMSMessage.BCSPNG);
								}
								else if(((MessageCAN0.DATAA&0xff)==0x10)&&((((MessageCAN0.DATAB)&0xff0000)>>8)==0x1600))
								{	
											BMSMessage.BCSdataflag=2;
											BMSMessage.BCSdatalen=(MessageCAN0.DATAA>>8)&0xff;
											BMSMessage.BCSPackCount=MessageCAN0.DATAA>>24;
											BMSMessage.BCSPNG=((MessageCAN0.DATAB)&0xff0000)>>8;								 
											BMS_DataAnswerHead(BMSMessage.BCSPackCount,BMSMessage.BCSPNG);
								}
								else if(((MessageCAN0.DATAA&0xff)==0x10)&&((((MessageCAN0.DATAB)&0xff0000)>>8)==0x1700))
								{	
											BMSMessage.BCSdataflag=3;
											BMSMessage.BCSdatalen=(MessageCAN0.DATAA>>8)&0xff;
											BMSMessage.BCSPackCount=MessageCAN0.DATAA>>24;
											BMSMessage.BCSPNG=((MessageCAN0.DATAB)&0xff0000)>>8;								 
											BMS_DataAnswerHead(BMSMessage.BCSPackCount,BMSMessage.BCSPNG);
								}				
					   break;
								
					default:
					     break;									
		}			
}		

void DataPackCEB_Analyse(void)	
{
			switch (ChargerMsg.ChargeStage)
			{   
				case 1:	
					   break;
				case 2:	
					   break;
        case 3:					
             memcpy(BatterMessage+((MessageCAN0.DATAA&0xff)-1)*7,&MessageCAN0.DATAA+1,7);   //当BMS接收到充电机的应答报文CTS后，开始建立连接发送数据DT（数据长度 为49Byte，共分为7包)	
             if((MessageCAN0.DATAA&0xff)==BMSMessage.BRMPackCount)   
						 {							 
							 BMS_DataAnswerEnd(BMSMessage.BRMdatalen,BMSMessage.BRMPNG);	
               BMS_CRM(0xAA);
               ChargerMsg.CRMcnt=0;	
               ChargerMsg.ChargeStage = 4;	   						 
						 }				
						 break;
				case 4:	
             memcpy(CFGMessage+((MessageCAN0.DATAA&0xff)-1)*7,&MessageCAN0.DATAA+1,7);       //当BMS接收到充电机的应答报文CTS后，开始建立连接发送数据DT（数据长度 为49Byte，共分为2包)
             BMSMessage.BatteryVoltage=	CFGMessage[8]+CFGMessage[9]*0xff;	
            if(BMSMessage.BatteryVoltage<=2000)
							BMSMessage.BatteryVoltage=2000;
             if((MessageCAN0.DATAA&0xff)==BMSMessage.CFGPackCount)   
						 {							 
							 BMS_DataAnswerEnd(BMSMessage.CFGdatalen,BMSMessage.CFGPNG);	
						   BMS_CTS();									 
						   BMS_CML();		
						   ChargerMsg.ChargeStage = 5;							 
						 }
						 break;
			  case 6:                                                                            //多个case走同样的语句
				case 7:
					  if(BMSMessage.BCSflag==1)
							{
							 memcpy(BCSMessage+((MessageCAN0.DATAA&0xff)-1)*7,&MessageCAN0.DATAA+1,7);   //当BMS接收到充电机的应答报文CTS后，开始建立连接发送数据DT（数据长度 为49Byte，共分为7包)	
							 if((MessageCAN0.DATAA&0xff)==BMSMessage.BCSPackCount)   
							 {							 
								 BMS_DataAnswerEnd(BMSMessage.BCSdatalen,BMSMessage.BCSPNG);							 
							 }
							 BMSMessage.BCSflag=0;
					    }
            else if(BMSMessage.BCSdataflag>=1)
						{
						   	if((MessageCAN0.DATAA&0xff)==BMSMessage.BCSPackCount)   
							 {							 
								 BMS_DataAnswerEnd(BMSMessage.BCSdatalen,BMSMessage.BCSPNG);							 
							 }	
                BMSMessage.BCSdataflag=0;							 
						}							
							 break;
				default:
					     break;								
			 }	       
			 BMSMessage.SoftVersion=BatterMessage[1]*0xff+BatterMessage[0];			 
}

void BRO_Analyse(void)	
{	
	   if((ChargerMsg.ChargeStage==5)||(ChargerMsg.ChargeStage==6))
		 {
			  ChargerMsg.ChargeStage=6 ;
			 if((MessageCAN0.DATAA&0xff)==0xaa)
			 {
				 BMSMessage.BROflag=2;
			 }else{
				  BMSMessage.BROflag=1;
			 }				 			 
	   } 
}

void BCL_Analyse(void)	
{ 
		if(ChargerMsg.ChargeStage>=6)
	 {         		     
				BMS_CCS();			 
				BMSMessage.RequestVoltage = MessageCAN0.DATAA&0xffff;
				BMSMessage.RequestCurrent = 4000-((MessageCAN0.DATAA&0xffff0000)>>16);	
				BMSMessage.RequestChargeMode  = MessageCAN0.DATAB&0xff;	
				BMSMessage.BCLflag=1; 
				BMSMessage.BCL1flag=1;
				ChargerMsg.CCScnt=0;
				ChargerMsg.BCLcnt=0;
	 }
}	

void BSM_Analyse(void)	
{  
	   if(ChargerMsg.ChargeStage==7)
		 {	      
	        BMSMessage.MAXSingleVoltageNO     = MessageCAN0.DATAA&0xff;
	        BMSMessage.MAXBatteryTemp         = (MessageCAN0.DATAA>>8)&0xff;	
	        BMSMessage.MAXBatteryTempNO       = (MessageCAN0.DATAA>>16)&0xff;
			    BMSMessage.MINBatteryTemp         = (MessageCAN0.DATAA>>24)&0xff;			 
			    BMSMessage.MINBatteryTempNO       = MessageCAN0.DATAB&0xff;						 
			    BMSMessage.SingleVoltageOHOL      = (MessageCAN0.DATAB>>8)&0x03;
           if (BMSMessage.SingleVoltageOHOL	==0x01)
					 {
					      ChargerMsg.StopReason=0xf0f40010;	
						    ChargerMsg.ChargeStage=8;	
					 }						 					 
			    BMSMessage.SOCOHOL = (MessageCAN0.DATAB>>8)&0x0c;	
           if (BMSMessage.SOCOHOL	==0x04)
					 {
					      ChargerMsg.StopReason=0xf0f40010;	
						    ChargerMsg.ChargeStage=8;	
					 }					 
			    BMSMessage.BatteryOC = (MessageCAN0.DATAB>>8)&0x30;
					 if (BMSMessage.BatteryOC	==0x10)
					 {
					      ChargerMsg.StopReason=0xf0f40010;	
						    ChargerMsg.ChargeStage=8;	
					 }						 
			    BMSMessage.BatteryTempOH  = (MessageCAN0.DATAB>>8)&0xc0; 
           if (BMSMessage.BatteryTempOH	==0x40)
					 {
					      ChargerMsg.StopReason=0xf0f40010;	
						    ChargerMsg.ChargeStage=8;	
					 }					 
			    BMSMessage.BatteryInsuFlag  = (MessageCAN0.DATAB>>16)&0x03;	
           if (BMSMessage.BatteryInsuFlag	==0x01)
					 {
					      ChargerMsg.StopReason=0xf0f40010;	
						    ChargerMsg.ChargeStage=8;	
					 }					 
			    BMSMessage.BatteryCnetFlag        = (MessageCAN0.DATAB>>16)&0x0c;
           if (BMSMessage.BatteryCnetFlag	==0x04)
					 {
					      ChargerMsg.StopReason=0xf0f40010;	
						    ChargerMsg.ChargeStage=8;	
					 }					 
			    BMSMessage.BatteryChgAlow   = (MessageCAN0.DATAB>>16)&0x30;	                                  //充电允许
					 if ((BMSMessage.BatteryChgAlow	== 0x10)&&(ChargerMsg.DCSwitchFlag==1))                       //充电允许，正在充电的情况下  时间清零  否则时间继续累加
					 {
                 BMSMessage.ChargeSuspendTime=0;
					 }        
           if ((BMSMessage.BatteryChgAlow == 0x00)&&(ChargerMsg.DCSwitchFlag==1))                       //充电禁止  正常无错误时10分钟内允许可恢复，超过10分钟则不允许回复
           {
						     ChargerMsg.PreCharge=0;
					 }						 			 			 
		 }
}	

void BST_Analyse(void)	
{		 	
      ChargerMsg.CSTcnt=0;	
  	if((ChargerMsg.ChargeStage<=8)&&(ChargerMsg.ChargeStage>=2))
		{
       ChargerMsg.ChargeStage=8;
			 BMSMessage.BSTflag=1;
			 BMS_CST(ChargerMsg.StopReason);							
		}		
}	

void BSD_Analyse(void)	
{    	
	      ChargerMsg.BSDcnt=0;
			  BMS_CSD();							
}	

void BEM_Analyse(void)	
{					
   if(MessageCAN0.DATAA!=0xfcf0f0f0)         //BEM错误 接收充电机报文超时
	 {
	   ChargerMsg.ChargeStage = 8;		 
	 }   
}	

void BMS_RECData_Pro(void)
{
/***************************************************************************************************************************************
*	任务循环的处理速度跟不上中断的处理速度，因此做一个缓冲区，由中断写入数据，任务循环处理数据，每处理完一帧数据，则把该针数据丢掉。
* 由于数据缓冲区的数据长度大小有限，当中断的写指针远远快过任务的读指针速度，则还是会出现丢包现象。
***************************************************************************************************************************************/
  	if(prMsgCAN0==&MsgCAN0BUF[CAN0_MSG_NUMBER-1])     /* 预留一个存储单元不存储，防止写指针指向最后一个存储单元时，读指针递增时溢出    */
	  {
			MessageCAN0 = *prMsgCAN0;
		  memset(prMsgCAN0,0,sizeof(*prMsgCAN0));         /*处理完一帧数据，就丢掉该包数据                                                 */			
			prMsgCAN0=MsgCAN0BUF;			                      /* 调整指针指向 ，由尾巴指向开始                                                 */
	  }
	  else                                             
		{
	     MessageCAN0 = *prMsgCAN0;
		   memset(prMsgCAN0,0,sizeof(*prMsgCAN0));        /*处理完一帧数据，就丢掉该包数据                                                 */
		   prMsgCAN0 ++;                                  /*指针递增必须放在最后，防止指针递增后进行重复的if处理                           */
	  }			
	switch(MessageCAN0.CANID)
	 {
		 case 0x182756F4:			      
        BHM_Analyse();	       		 
		    break;
		 case 0x1cec56f4:
			  DataPackCEC_Analyse();
			  break;
		 case 0x1ceb56f4:
			  DataPackCEB_Analyse();
			  break;
		 case 0x100956f4:
         BRO_Analyse();
		    break;
		 case 0x181056f4:
         BCL_Analyse();		 
		    break;
		 case 0x181356f4:
         BSM_Analyse();
			 break;
		 case 0x101956f4:
         BST_Analyse();	
		    break;		 
		 case 0x181c56f4:
         BSD_Analyse();	
		    break;
		 case 0x081e56f4:	
         BEM_Analyse();	
         break;		 
		 default:
			   break ;		 				 
	 }
	 memset(&MessageCAN0,0,sizeof(MessageCAN0));//清空CAN的数据， 防止重复处理
}
