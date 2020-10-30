/****************************************Copyright (c)****************************************************
**                                     Tomorn  Co.,LTD.
**                                     
**                                   http://www.tomorn.cn
**                                       wujikun
�ļ����ƣ�BMS.C
��    �ܣ��복��BMSͨѶ
��дʱ�䣺2019.10.18
�� д �ˣ�
ע    �⣺
                   0xXXXXF456 Ϊ������BMS
                   0xXXXX56F4 ΪBMS������
1 ����
         ����(CRM)     ----->BMS       (00 A8 00 00 00 00 00 00  )
                                         byte0��00 ����BMS���֣����BMS�л�Ӧ��ΪAA��
                                         byte1��A8������ţ����ǹ�˾Ĭ��ΪA8
                                         byte2-7:6���ֽ�Ϊ�������վ���ڵı�ţ���ѡ��Ϣ��

         BMS(RTS)        ----->����    (10 31 00 06 ff 00 02 00 )     BMS����RTS����(ID:1CEC56F4)��֪ͨ����׼�����Ͷ��ٰ�����
                                                                        byte0: 10 �����ַ�����ʾ֪ͨ��Ҫ�����
                                                                        byte1: 0x29=49 ��Ҫ��49�ֽ�����
                                                                        byte3: 07 ��ʾ��������ܹ�7֡
                                                                        byte5-7: 0x00 02 00=512 PGNΪ512����BMS�ͳ���ʶ����

         ����(CTS)     ----->BMS       (11 06 01 FF FF 00 02 00 )     �������յ�BMS���͵�RTS���ĺ�����Ӧ���źţ��ظ�CTS��BMS
                                                                        byte0��11 �����ֱ�ʾ�����յ��˶��Э������
                                                                        byte1: 06 �������Ϊ6֡
                                                                        byte2: 01 ��һ��Ҫ�������ݵİ�ͷ
                                                                        byte5-7:00 02 00 PGNΪ512����BMS�ͳ���ʶ����
                                                                        
         BMS(DT)         ----->����    ��7�����ݣ�                    ��BMS���յ�������Ӧ����CTS�󣬿�ʼ�������ӷ�������DT�����ݳ���Ϊ41Byte������Ϊ6��
                                                                        8�ֽ�������ʵ��7�ֽ����ã��ܹ�41�ֽ�����
                                                                        01������Ϊbyte1-7��Ӧ����0-6,
                                                                        02������Ϊbyte0-7��Ӧ����7-13���Դ����ƺ����
                                         0x1ceb56f4 01 01 01 00 06 bc 02 fa
                                         0x1ceb56f4 02 0b ff ff ff ff ff ff
				                                                                ����0-2:01 01 00 BMSͨѶЭ���V1.1
                                                                        ����3: ������ͣ�01H��Ǧ���أ�02H�������أ�03H��������﮵�أ�04H������﮵�أ�05H�������أ�06H����Ԫ���ϵ�أ�07H���ۺ�������ӵ�أ�08H������﮵�أ�FFH���������
                                                                        ����4-5��bc 02:�������
                                                                        02bc=700*0.1=70A.h
                                                                        ����6-7��fa0b��ض��ѹ
                                                                        0bfa=3058*0.1=305.8V
                                                                        ����8-40�ǿ�ѡ���ݣ�û��Ĭ��ΪFF
                                                                        
																��ط�����������																				
			   ����(EM)      ----->BMS	      (13 29 00 06 ff 00 02 00)     ���������ܵ��˽�����BMS���͵����ݱ���DT�󣬻ظ�CM��BMS������Ϣ���� 

         ����(CRM)     ----->BMS	      (aa A8 00 00 00 00 00 00)     �������ֳɹ�ָ��  
				 
				 
2 ��������

         BMS(RTS)         ----->����     (10 0d 00 02 ff 00 06 00)    ����BMS����RTS������ ֪ͨ����׼�����Ͷ��ٰ�����
				
				����(CTS)      ----->BMS	      (11 02 01 FF FF 00 06 00)    �������յ�BMS���͵�RTS���ĺ�����Ӧ���źţ��ظ�CTS��BMS   
				
				BMS(DT)          ----->����     ��BMS���յ�������Ӧ����CTS�󣬿�ʼ�������ӷ�������DT�����ݳ���Ϊ13Byte������Ϊ2��)         �൱�� 0x80656f4
				                                   �������س���������
																			     �� 1~2   �ֽ�	���嶯����������������ѹ
																				   �� 3~4   �ֽ�	������������
																				   �� 5~6   �ֽ�	���ر��������
																				   �� 7~8   �ֽ�	����������ܵ�ѹ
																				   �� 9     �ֽ�	��������¶�
																				   �� 10~11 �ֽ�	�����������غɵ�״̬
																				   �� 12    �ֽ�	�������������ܵ�ѹ
															                     0x1cec56f4 10 0d 00 02 ff 00 06 00
                                                   0x1cecf456 11 02 01 ff ff 00 06 00
			                                                            10 BMS���� 2��13�ֽ����� PNGΪ000600=1536.
                                                                  11 �����յ�BMS�������2�����ݣ���һ�����ݰ�ͷΪ01��PNGΪ1536
                                                  0x1ceb56f401 93 01 1c 0c df 00 34
                                                  0x1ceb56f402 0d 62 e8 03 b8 0d ff
                                                                  ����0-1: 9301 ��ߵ��������ѹ0193=403*0.01=4.03V
                                                                  ����2-3:1c0c ����������ѹ0c1c=3100*0.1=310������Ϊ400-310=90A��������-400Aƫ������
                                                                  ����4-5��df00 �������0x00df=223*0.1=22.3KW.h
                                                                  ����6-7:340d ����������ܵ�ѹ0x0d34=3380*0.1=338V
                                                                  ����8:62��������¶�0x62=98-40=58�ȣ��¶���40��ƫ�ơ�
                                                                  ����9-10��e803 ���SOCֵ0x03e8=1000*0.1=100%��
                                                                  ����11-12��b80d �����ѹ0x0db8=3512*0.1=351.2V								   

        ����(TPCM_EM) ----->BMS	       (13 0d 00 02 ff 00 06 00)       ���������ܵ��˽�����BMS���͵����ݱ���DT�󣬻ظ�CM��BMS������Ϣ����Ӧ��
				
				����(CTS)     ----->BMS        (00 00 00 00 00 00 00  )	      ��������ʱ��ͬ����ϢCTS��BMS
				                                 
                                                                  byte0��BCD���� byte1��BCD���
                                                                  byte2��BCD��ʱ byte3��BCD����
                                                                  byte4��BCD���� byte5��BCD����
                                                                  ע����BCD��Ϊʮ���� 59=59��               
		
				����(CML)     ----->BMS        (68 10 d0 07 b8 0b)             ��������������CML��BMS  Ӣ���� 300��012C��---750(02EE)V  10A����
                                                     0x1808f456 4c 1d d0 07 d0 07 00 00
				                                                        byte0-1:4c1d ��������ѹ1d4c=7491=7491*0.1=749.1V.
                                                                byte 2-3��d007��������ѹ200V
                                                                byte4-5��d007����������400-200=200A
				
				BMS(BRO)        ----->����     (aa               )             BMS���͵�س��׼������״̬BRO������
				                                                       aa ׼������ 00δ׼����
				
        ����(CRO)     ----->BMS        (aa               )             �������յ�BMS���͵�BRO��Ϣ���Ӧ�������׼������״̬CRO        
				                                                       aa ׼������ 00δ׼����
				
3  ���׶�

       BMS(BCL)        ----->����      (E2 18 76 0C 02 )               BMS���͵�س�缶��BCL��������ID��181056F4��. Byte1�� Byte2�ǵ�ѹ��Byte 3��Byte4�ǵ���
                                                         0x181056f4 98 0d 10 0e 01 00 00 00
                                                                         byte0-1:980D�����ѹ0d98=348V
                                                                         byte2-3:100e�������0e10=3600*0.1=360-400=40A
                                                                         byte4��01���ģʽ 01��ѹ��02����

			 BMS(BCS)   ----->����      (10 09 00 02 ff 00 aa 00)       ����BMS����BCS���ģ�֪ͨ����׼�����Ͷ��ٰ�����
			                                             0x1cec56f4 10 09 00 02 ff 00 11 00
			                                                          PNG 001100 =4352 ��س����״̬����   
			
       ����    ------>BMS	  		  (11 02 01 ff ff 00 11 00)	     �������յ�BMS���͵�BCS���ĺ�����Ӧ���źţ��ظ���BMS  
			 
			 BMS(DT)   ----->����       �����ݳ���Ϊ9Byte������Ϊ2��)     ��BMS���յ�������Ӧ����CTS�󣬿�ʼ�������ӷ�������DT  BMS���͵�س����״̬BCS������
			                                    0x1ceb56f4 01 77 0e 96 0f 7e c1 42
                                                0x1ceb56f4 02 58 02 ff ff ff ff ff
                                                           ����0-1��770e����ѹ���0e77=370.3V
                                                           ����2-3��960f���������0f96=3990*0.1-400=0.1A  
                                                           ����4-5:7ec1 ��ߵ����ѹ����ţ���ߵ����ѹ0-11λ��0x17e=382*0.01=3.82,�������Ϊ12-15λ0X07=7,��7���ص���
                                                           ����6:  42 ��ǰ���SOC=0x42=66%
                                                           ����7-8��5802ʣ����ʱ��0x0258=600min����λ����
                                                           
                                                                        BMS��س����״̬     1--2 ����ѹ����ֵ��V��  3--4 ����������ֵ��A��  5--6 ��ߵ��嶯�����ص�ѹ�������
                                                                                              7 ��ǰ�ɵ�״̬SOC��%�� 8--9  ����ʣ����ʱ�䣨min��
			 ����      ----->BMS	  	   (13 09 00 02 ff ff ff ff ff)    ���������ܵ��˽�����BMS���͵����ݱ���DT�󣬻ظ���BMS������Ϣ����Ӧ��

			 ����(CCS) ----->BMS	       (00 00 a0 0f 000 00)            �������ͳ��״̬CCS��BMS
			                                        0x1812f456 b8 0d a0 0f 00 00 00 00
			                                            byte0-1��b80d��ѹ���ֵ0x0db8=3512=351.2V
                                                        byte2-3��a00f�������ֵ0x0fa0=4000=0A
                                                        byte4-5:0000�ۼƳ��ʱ�䣬��λ����
       BMS(BSM)   ----->����                                           
                                                    0x181356f4 4e 4e 91 4d 83 04 10 00
                                                        byte0��4e��߱��0x4e=78��
                                                        byte1:4e��ߵ����¶�0x4e=78-50=28��
                                                        byte2:91����¶ȱ��0x91=145��
                                                        byte3:4d����¶�0x4d=77-50=27��
                                                        byte4��83��͵�ر�� 0x83=131��
                                                                                            ע�������¶�ƫ������-50��
                                                        byte5-6:0410���״̬��Ϣ��0X1004=0B00010000 0000 0100����2λһ����Ϣ
                                                                bit 0-1��0B00�����ѹ״̬ 00��������01���ߣ�10���ͣ�
                                                                bit 2-3:0B01���SOC ״̬00����01����10����
                                                                bit 4-5: 0B00����������00����01����10������
                                                                bit 6-7:0B00����¶�00����01����10����
                                                                bit 8-9:0B00 ��Ե״̬00����01������10������
                                                                bit 10-11:0B00 ���������״̬00����01������10������
                                                                bit 8-9:0B01 �������00��ֹ01����



                                                         
			                                                             BMSͨ�����ݴ���Э�鷢�͵����ѹBMV�����������岽������ֽ׶ε����ݴ���Э��һ������ѡ��
                                                                         BMS�����������¶�BMT������.�����岽������ֽ׶ε����ݴ���Э��һ����  ��ѡ��
		
              BMS(BST)    ----->����
                                        0x101956f4 10 00 00 00 00 00 00 00
                                               byte0:10 BMS��ֹ���ԭ�� 0B0001 0000
                                               bite0-1������SOCֵ 00δ�ﵽ 01�ﵽ10������
                                               bite2-3���趨��ѹֵ 00 δ�ﵽ01�ﵽ10������
                                               bite4-5���趨�����ѹֵ 00 δ�ﵽ01�ﵽ10������
                                                   bit:1-2��0x00=0B0000 0000 0000 0000 ��BMS��ֹ������ԭ�� bite0-1����Ե bite2-3���������������bite4-5��BMSԪ��������������� 
                                               bite6-7���������������
                                               bite8-9��������¶ȹ���bite10-11���������� 00������01���ϣ�10������
                                              

              ����(CST) ----->BMS	    0x101af456 00 00 00 00 00 00 00 00

                                             BYTE0 ������ֹ���ԭ��
                                             BYTE1-2 ������ֹ������ԭ��
                                             BYTE3 ������ֹ������ԭ��
                                             1��������ֹ���ԭ��
                                                a)1~2λ���ﵽ�����趨��������ֹ��00��������01���ﵽ�趨������ֹ��10��������״̬��
                                                b)3~4λ���˹���ֹ��00��������01���˹���ֹ��10��������״̬��
                                                c)5~6λ��������ֹ��00��������01��������ֹ��10��������״̬��
                                             2��������ֹ������ԭ��
                                                a)1~2λ���������¹��ϣ�00���¶�������01���������£�10��������״̬��
                                                b)3~4λ��������������ϣ�00��������������01�����ϣ�10��������״̬��
                                                c)5~6λ�������ڲ����¹��ϣ�00���ڲ��¶�������01���ڲ����£�10�������ţ�
                                                d)7~8λ������������ܴ��ͣ�00������������01�����ܴ��ͣ�10�������ţ�
                                                e)9~10λ��������ͣ���ϣ�00��������01����ͣ��10��������״̬��
                                                f)11~12λ���������ϣ�00��������01�����ϣ�10��������״̬��
                                             3��������ֹ������ԭ��
                                                a)1~2λ��������ƥ�䣨00������ƥ�䣬01��������ƥ�䣬10��������״̬��
                                                b)3~4λ����ѹ�쳣��00��������01���쳣��10��������״̬��
																								
																								
4  �����׶�																							
              BMS(BSD)   ----->����               
                                         0x181C56F4
                                           BYTE0 ��ֹʱSOC ֵ��������1%��ƫ������0��
                                           BYTE1 �������ص�����͵�ѹ��������0.01��ƫ������0��
                                           BYTE2
                                           BYTE3 �������ص�����ߵ�ѹ��������0.01��ƫ������0��
                                           BYTE4
                                           BYTE5 ������������¶ȣ�������1��ƫ������-50��
                                           BYTE6 ������������¶ȣ�������1��ƫ������-50��

              ����(CSD) ----->BMS
                                          0x181DF456
                                              BYTE0 �ۼƳ��ʱ�䣨������1min��ƫ������0����Χ��0~600��
                                              BYTE1
                                              BYTE2 �ۼ����������������0.1kw��h��ƫ������0����Χ��0~1000��
                                              BYTE3
                                              BYTE4 �������

5  ������
          BMS(BEM)   ----->����
         
                          ID:081E56F4 (PGN=7680)

                        BYTE0 Bit0-Bit1 ����SPN2560=0X00 ������ʶ���ĳ�ʱ��00��������01����ʱ��10��������״̬��
                              Bit2-Bit3 ����SPN2560=0XAA ������ʶ���ĳ�ʱ��00��������01����ʱ��10��������״̬��
                        BYTE1 Bit0-Bit1 ���ܳ�����ʱ��ͬ���ͳ�������������ĳ�ʱ��00��������01����ʱ��10��������״̬��
                              Bit2-Bit3 ���ܳ�����ɳ��׼�����ĳ�ʱ��00��������01����ʱ��10��������״̬��
                        BYTE2 Bit0-Bit1 ���ܳ������״̬���ĳ�ʱ��00��������01����ʱ��10��������״̬��
                              Bit2-Bit3 ���ܳ�����ֹ���ĳ�ʱ��00��������01����ʱ��10��������״̬��
                        BYTE3 Bit0-Bit1 ���ܳ������ͳ�Ʊ��ĳ�ʱ��00��������01����ʱ��10��������״̬��

         ����(CSD) ----->BMS 
                         ID:081FF456 (PGN=7936)
                              BYTE0 Bit0-Bit1 ����BMS �ͳ����ı�ʶ���ĳ�ʱ��00��������01����ʱ��10��������״̬��
                              BYTE1 Bit0-Bit1 ���ܵ�س��������ĳ�ʱ��00��������01����ʱ��10��������״̬��
                              Bit2-Bit3 ����BMS ��ɳ��ǰ׼�����ĳ�ʱ��00��������01����ʱ��10��������״̬��
                              BYTE2 Bit0-Bit1 ���ܵ�س����״̬���ĳ�ʱ��00��������01����ʱ��10��������״̬��
                              Bit2-Bit3 ���ܵ�س�������ĳ�ʱ��00��������01����ʱ��10��������״̬��
                              Bit4-Bit5 ����BMS ��ֹ��籨�ĳ�ʱ��00��������01����ʱ��10��������״̬��
                              BYTE3 Bit0-Bit1 ����BMS ���ͳ�Ʊ��ĳ�ʱ��00��������01����ʱ��10��������״̬��

	
**********************************************************************************************************************************/
#include <bms.h>
#include <insulation.h>
#include <adc.h>

unsigned char BatterMessage[49];         //��ز������ݰ� 
unsigned char CFGMessage[13];            //���ò������ݰ� 
unsigned char BCSMessage[9];             //���������ݰ�

uint8_t InsulationFlag  ;   //  1����ʼ����Ե���  2����Ե������ 3����Ե���������������ꡣ
uint8_t OutVoltageDetFlag;  //  1����ʼ����ص�ѹ  2����ص�ѹ���ͨ��   3����ص�ѹ��ⲻͨ��

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
	 ChargerMsg.ChargeStage=0; //�׶�����
   InsulationFlag    = 0;    //��Ե���״̬����
   OutVoltageDetFlag = 0;	   //�ⲿ��ѹ�������
	 ChargerMsg.PreCharge=0;   //Ԥ���ʶ	
	 ChargerMsg.CHMcnt=0;      //����������
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
	 ChargerMsg.ChargedTime=0;       //ʱ������
	 ChargerMsg.StopReason=0;        //����ֹͣԭ������
	 ChargerMsg.StartCompleteflag=0;  //�����ɹ���־
   ChargerMsg.StopCompleteflag=0;  //ֹͣ�ɹ���־	
   ChargerMsg.SE12SwitchFlag=0;
	 ChargerMsg.DCSwitchFlag=0;
	 BMSMessage.BHMflag=0;	   //�յ�BHM����	 
	 BMSMessage.BRMflag=0;	   //�յ�BRM����
	 BMSMessage.BCPflag=0;	   //�յ�BCP����	 
	 BMSMessage.BROflag=0;	   //�յ�BRO�������ı�־
	 BMSMessage.BCLflag=0;     //�յ�BCL����
	 BMSMessage.BCL1flag=0;    //�״��յ�BCL����	 
	 BMSMessage.BCSflag=0;	   //�յ�BCS����
	 BMSMessage.BCS1flag=0;	   //�״��յ�BCS����		 
	 BMSMessage.ChargeSuspendTime=0;  //�������ͣʱ������
}

void ChargeStart(void)
{
	  ChargerMsgInit();	
}

void ChargeStop(void)
{
		ChargerMsg.StopCompleteflag=1;  //ֹͣ�ɹ���־
		ChargerMsg.ChargeStage=0;
}

void BMSMain (void)
{	
	  ChargerMsgInit();		
  while (1) 
 {							
    OSTimeDlyHMSM(0,0,0,1);	
	  if((ADstatus != ADC4V)&&(ChargerMsg.ChargeStage>=2))                                // CC�쳣״̬����
	 {
		 ChargerMsg.ChargeStage=8;
	 }
	 else if((ADstatus != ADC4V)&&(ChargerMsg.ChargeStage==1))                            // CC�쳣״̬����
	 {
	   ChargerMsg.ChargeStage=0;
	 	 //δ��ǹ������ǹ��ʾ
	 }		 
		BMS_RECData_Pro();                                                                 // ������׮���������� ����Ҫ�Ǳ��������� 	 	 
	switch (ChargerMsg.ChargeStage)
	{
    case 1: 	
		    	ChargeStart();
			    LOCK_SWITCH_ON();
				  OSTimeDlyHMSM(0,0,0,100);
				  SE12V_SWITCH_ON();                                                           //���ϸ�����Դ
		      ChargerMsg.SE12SwitchFlag=1;
			    OSTimeDlyHMSM(0,0,0,100);
				  AC_SWITCH_ON();                                                              //���Ͻ����Ӵ���	
					OSTimeDlyHMSM(0,0,1,0);
		      ChargerMsg.ChargeStage=2;
		     break;		
		case 2:	 	                                                                         //���ڷ���Э��汾			
			   ChargerMsg.CHMcnt++;
		     if((ChargerMsg.CHMcnt%250)==0)                                                //��س����״̬��250ms����һ��  
		     {       
				    BMS_CHM();
		     }		
				//BMSͨѶ��ʱ ��CHM����ʱ�䳬��5��ʱ	�ж�ͨѶ��ʱ	
         if((ChargerMsg.CHMcnt>=8000)&&(BMSMessage.BHMflag==0))
					 {
					   ChargerMsg.ChargeStage=8;
					 }					
	       break; 								
	  case 3:				                                                                      //���ڷ��Ϳ�ʼ���ֱ���
	   		 ChargerMsg.CRMcnt++;			
         if(ChargerMsg.CRMcnt<5*1000)			
				 {
		       if(BMSMessage.BRMflag==0)
			    	{
							if((ChargerMsg.CRMcnt%250)==0)                                             //��س����״̬��250ms����һ��  
							{       
								BMS_CRM(0x00);
							}
						}
					}
         else if(ChargerMsg.CRMcnt>=5*1000)	
						{
						  BMS_CEM(0xfdf0c0fc);                                                     // DN.1001 DN.1002 DN.1003 ����BMS��ʶ���ĳ�ʱ
							ChargerMsg.ChargeStage=9;
						}																		
					break;						
	 	 case 4:	
			 	    ChargerMsg.CRMcnt++;
          	if(ChargerMsg.CRMcnt<5*1000)
            {							
								 if((ChargerMsg.CRMcnt%250)==0)                                        //��س����״̬��250ms����һ��  
								{       
									BMS_CRM(0xaa);
								}
						}
						 if(ChargerMsg.CRMcnt>=5*1000)	                                           // DN.1004 DN.2001 DN.2002����BMS���ò�����ʱ
						{
									BMS_CEM(0xfcf1c0fc); 
					        ChargerMsg.ChargeStage = 9;							
						}			     
					break;						
		 case 5:				                                                                   //���ڷ�����������������	
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
             else if	(ChargerMsg.CTScnt>=5*1000)	                                    //DN.2003 DN.2004 DN.2006 ����BMS��ɳ��׼����ʱ               
							 {							
					          BMS_CEM(0xfcf4c0fc); 	
					          ChargerMsg.ChargeStage = 9;								 
							 }																						
							break;								 
		case 6:	 	                                                                                        // ���ڷ�������״̬����
			      ChargerMsg.CROcnt++;	 			
					if(ChargerMsg.CROcnt<60*1000)	
					{								
               if((BMSMessage.BCL1flag==0)&&(BMSMessage.BCS1flag==0))                                  //BCL��BCS��û���յ�ʱ
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
												if((ChargerMsg.CROcnt%250)==0)                                                //��س����״̬��250ms����һ��  
												 {
                           if(BMSMessage.BROflag==2)	                                        //��һֱΪ׼����ɣ���һֱ��CRO=0x00��     
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
												 //���������ѹ�Ƿ�����Ƿ񳬹�5%
												 break;											
											default:
													break;									
										}
							  	}																																					 
						 }	
					 else if(ChargerMsg.CROcnt>=60*1000)                                         //DN.2005 ����BMS��ɳ��׼����ʱ    
						 {			
                  if(BMSMessage.BROflag!=2)	
									{										
							      BMS_CEM(0xfcf4c0fc);
					          ChargerMsg.ChargeStage = 9;										
									}										
							}								 				
          break;						
		case 7:                                                                               //���׶� 
			      ChargerMsg.CROcnt++;	
			      ChargerMsg.CCScnt++;                                                      
		        ChargerMsg.BCLcnt++; 	
            ChargerMsg.BCScnt++; 		

		      if((BMSMessage.BCL1flag==0)||(BMSMessage.BCS1flag==0))                          //�״ε�BCL1��BCS1ֻҪһ�����յ��������
		      {
						if((ChargerMsg.CROcnt%250)==0)                                                //��س����״̬��250ms����һ��  
				    {									 
					   	BMS_CRO(0xaa);	
						}
						 if(BMSMessage.BCS1flag==1)                                                   // DN.3002 DN.3004 ���յ�BCSδ���յ�BCL
						 {
							 if(ChargerMsg.BCLcnt>1000)
								{
									 BMS_CEM(0xfcf4c0fc);
					         ChargerMsg.ChargeStage = 9;									
								}
						  }
						 if(BMSMessage.BCL1flag==0)                                                   // DN.3001 DN.3003 ���յ�BCLδ���յ�BCS
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
						 if((BMSMessage.ChargeSuspendTime<(10*60))&&(BMSMessage.BatteryChgAlow	=0x10))   //�����ͣ10���� �ɻָ�
						 {
									if(ChargerMsg.BCLcnt>1000)                                                  // DN.3006 DN.3008 ���յ�BCL�ж�
									{
										 BMS_CEM(0xfcf4c0fc); 
										 ChargerMsg.ChargeStage = 9;
									}						
									if(ChargerMsg.BCScnt>5*1000)                                                // DN.3005 DN.3007 ���յ�BCS�ж�
									{															
										 BMS_CEM(0xfcf4c0fc); 	
										 ChargerMsg.ChargeStage = 9;							
									}
							}else if((BMSMessage.ChargeSuspendTime>(10*60))&&(BMSMessage.BatteryChgAlow	=0x00))//�����ͣ����10���ӣ����ɻָ�
						 {
							 ChargerMsg.ChargeStage=8;
						 }					 
					}										
	       break;					
		case 8:                                                                          
					ChargerMsg.CSTcnt++;         
					ChargerMsg.BSDcnt++;			
				 if(BMSMessage.BSTflag==0)                                                         //����ͣ��
				 {
						if((ChargerMsg.CSTcnt%10)==0)                                                  //��س����״̬��250ms����һ��  
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
				 else if(BMSMessage.BSTflag==1)                                                     //����ͣ��
				 {
					 	if((ChargerMsg.DCSwitchFlag==1)&&(ChargerMsg.ChargeCurrent<=50))                                      
						{						
							DC_SWITCH_OFF();
							ChargerMsg.DCSwitchFlag=0;
							ChargerMsg.ChargeStage=9;					
						 }
						if((ChargerMsg.CSTcnt%10)==0)                                                   //��س����״̬��250ms����һ��  
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
		      SE12V_SWITCH_OFF();                                                         //�Ͽ�������Դ
					OSTimeDlyHMSM(0,0,1,0);
				  LOCK_SWITCH_OFF();
	      	OSTimeDlyHMSM(0,0,1,0);			
					AC_SWITCH_OFF();                                                            //�Ͽ������Ӵ���
					ChargerMsg.ChargeStage=10;
	       break;		
    case 10:                                                                          //�������
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

void BMS_CRO(uint8_t data)	           	// ��ز��� �������س��������� aa
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

void BMS_DataAnswerHead(uint8_t packlen,uint16_t png)    //�����յ�BMS���͵�RTS���ĺ�����Ӧ���źţ��ظ�CTS��BMS  �������ý׶� 
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

void BMS_DataAnswerEnd(uint8_t datalen,uint16_t png)    //�����յ�BMS���͵�RTS���ĺ�����Ӧ���źţ��ظ�CTS��BMS  �������ý׶� 
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
	 CAN_Data[0]=reason&0xff;              //������ֹ���ԭ��
	 CAN_Data[1]=(reason>>8)&0xff;         //������ֹ������ԭ��
	 CAN_Data[2]=(reason>>16)&0xff; 
	 CAN_Data[3]=(reason>>24)&0xff;        //������ֹ������ԭ��
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
		 BMSMessage.BHMflag=1;	                                 //�յ�BRM����
   if(ChargerMsg.ChargeStage==2)
	 {
		   if(PRINT_STRING)
	     Print("%s\n", "chargestate 1 ,  handshake !"); 
       BMSMessage.MAXVoltage= MessageCAN0.DATAA&0xffff;			 //��ѹ����Ե���ʹ��
			 			 
			 /**  ���׮���K1��K2����ѹС��10V�������˾ͽ��о�Ե��� **/
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
             memcpy(BatterMessage+((MessageCAN0.DATAA&0xff)-1)*7,&MessageCAN0.DATAA+1,7);   //��BMS���յ�������Ӧ����CTS�󣬿�ʼ�������ӷ�������DT�����ݳ��� Ϊ49Byte������Ϊ7��)	
             if((MessageCAN0.DATAA&0xff)==BMSMessage.BRMPackCount)   
						 {							 
							 BMS_DataAnswerEnd(BMSMessage.BRMdatalen,BMSMessage.BRMPNG);	
               BMS_CRM(0xAA);
               ChargerMsg.CRMcnt=0;	
               ChargerMsg.ChargeStage = 4;	   						 
						 }				
						 break;
				case 4:	
             memcpy(CFGMessage+((MessageCAN0.DATAA&0xff)-1)*7,&MessageCAN0.DATAA+1,7);       //��BMS���յ�������Ӧ����CTS�󣬿�ʼ�������ӷ�������DT�����ݳ��� Ϊ49Byte������Ϊ2��)
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
			  case 6:                                                                            //���case��ͬ�������
				case 7:
					  if(BMSMessage.BCSflag==1)
							{
							 memcpy(BCSMessage+((MessageCAN0.DATAA&0xff)-1)*7,&MessageCAN0.DATAA+1,7);   //��BMS���յ�������Ӧ����CTS�󣬿�ʼ�������ӷ�������DT�����ݳ��� Ϊ49Byte������Ϊ7��)	
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
			    BMSMessage.BatteryChgAlow   = (MessageCAN0.DATAB>>16)&0x30;	                                  //�������
					 if ((BMSMessage.BatteryChgAlow	== 0x10)&&(ChargerMsg.DCSwitchFlag==1))                       //����������ڳ��������  ʱ������  ����ʱ������ۼ�
					 {
                 BMSMessage.ChargeSuspendTime=0;
					 }        
           if ((BMSMessage.BatteryChgAlow == 0x00)&&(ChargerMsg.DCSwitchFlag==1))                       //����ֹ  �����޴���ʱ10����������ɻָ�������10����������ظ�
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
   if(MessageCAN0.DATAA!=0xfcf0f0f0)         //BEM���� ���ճ������ĳ�ʱ
	 {
	   ChargerMsg.ChargeStage = 8;		 
	 }   
}	

void BMS_RECData_Pro(void)
{
/***************************************************************************************************************************************
*	����ѭ���Ĵ����ٶȸ������жϵĴ����ٶȣ������һ�������������ж�д�����ݣ�����ѭ���������ݣ�ÿ������һ֡���ݣ���Ѹ������ݶ�����
* �������ݻ����������ݳ��ȴ�С���ޣ����жϵ�дָ��ԶԶ�������Ķ�ָ���ٶȣ����ǻ���ֶ�������
***************************************************************************************************************************************/
  	if(prMsgCAN0==&MsgCAN0BUF[CAN0_MSG_NUMBER-1])     /* Ԥ��һ���洢��Ԫ���洢����ֹдָ��ָ�����һ���洢��Ԫʱ����ָ�����ʱ���    */
	  {
			MessageCAN0 = *prMsgCAN0;
		  memset(prMsgCAN0,0,sizeof(*prMsgCAN0));         /*������һ֡���ݣ��Ͷ����ð�����                                                 */			
			prMsgCAN0=MsgCAN0BUF;			                      /* ����ָ��ָ�� ����β��ָ��ʼ                                                 */
	  }
	  else                                             
		{
	     MessageCAN0 = *prMsgCAN0;
		   memset(prMsgCAN0,0,sizeof(*prMsgCAN0));        /*������һ֡���ݣ��Ͷ����ð�����                                                 */
		   prMsgCAN0 ++;                                  /*ָ��������������󣬷�ָֹ�����������ظ���if����                           */
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
	 memset(&MessageCAN0,0,sizeof(MessageCAN0));//���CAN�����ݣ� ��ֹ�ظ�����
}
