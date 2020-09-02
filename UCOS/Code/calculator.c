/****************************************Copyright (c)****************************************************
**                                     Tomorn  Co.,LTD.
**                                     
**                                   http://www.tomorn.cn
**                                       wujikun
**--------------File Info---------------------------------------------------------------------------------
** File Name:               calculator.c
** Last modified Date:      2018.08.20
** Last Version:            1.0
** Description:             
*********************************************************************************************************/
#include <calculator.h>
/*********************************************************************************************************
1字节2位BCD数据转换成整数
**********************************************************************************************************/
uint8_t BCD_To_HEX(uint8_t bcd)
{
	return (bcd/16*10 + bcd%16);
}


/*********************************************************************************************************
1字节整数转换成BCD数据
*********************************************************************************************************/
uint8_t HEX_To_BCD(uint8_t hex)
{
	return (hex/10*16 + hex%10);	
	
}	
	
/*********************************************************************************************************
N字节2位BCD数组转换成 1字节32位整数(BCD数组低位在前)
*********************************************************************************************************/
unsigned int NBCD_To_HEX_L(unsigned char *dbuf,unsigned int len)
{	
	unsigned int i,ret=0;
	
	for(i=0;i<len;i++){
		ret = ret*100+BCD_To_HEX(dbuf[len-i-1]);
	}
	return ret;
}

/*********************************************************************************************************
N字节2位BCD数组转换成 1字节32位整数(BCD数组高位在前)
*********************************************************************************************************/
unsigned int NBCD_To_HEX_H(unsigned char *dbuf,unsigned int len)
{	
	unsigned int i,ret=0;

	ret = BCD_To_HEX(dbuf[0]);

	for(i=1;i<len;i++)
	{
	 	ret = ret*100 + BCD_To_HEX(dbuf[i]);
	}
	return ret;
}

/*********************************************************************************************************
** Function name:           CheckSum	   
** Descriptions:            系统参数初始化	
** input parameters:        *start	:	指向数据的指针
**			                  	*end	:	计算的数据的尾指针
** output parameters:       无      
** Returned value:          无 
*********************************************************************************************************/
uint8_t	CheckSum(uint8_t *start, uint8_t *end)
{
	uint32_t	cs;	
	for(cs = 0; start < end; start++){
		cs	+= *start;
	}
	return (uint8_t)cs;
}

/******************************************************************************************
和校验计算函数
******************************************************************************************/
uint8_t CheckSum_CS(uint8_t *start,uint8_t len)
{
	uint32_t sum = 0;
	uint8_t i = 0;
	for(i=0;i<len;i++)
		sum += start[i];
	return (uint8_t)sum%256;
}


/*********************************************************************************************************
** Function name:           ASCII_To_HEX	   
** Descriptions:            系统参数初始化	
** input parameters:        len　数据长度
                            dot　小数点位数返回
** output parameters:       无      
** Returned value:          无 
*********************************************************************************************************/
uint32_t ASCII_To_HEX(uint8_t *data,uint8_t len,uint8_t dot)
{
		uint8_t i,cnt=0,ndot=0,dotflag=0;
		uint32_t tradata=0,xx=0;
	  uint8_t dotlen = 0;
		if(len>8)			return tradata;
		for(i=0;i<len;i++)
		{
			if((*(data+i)>=0x30&&*(data+i)<=0x39)||(*(data+i)==0x2e))
			{
				if(*(data+i)!=0x2e)
				{
					if(dotflag)
					{
						dotflag = 0;
						ndot++;
					}
					if(ndot>1)
						return 0xffffffff;
					tradata *=10;
					tradata +=(*(data+i)-0x30);
				}
				else
				{
					cnt++;
					dotlen = i;
					dotflag=1;
				}
			}
			else 
				return 0xffffffff;
		}
		if(cnt>1) 
			return 0xffffffff;
		
	if(dotlen==0) //输入的是整数
	{
		if(dot>0)
		{
			xx = 1;
			for(i=0;i<dot;i++)
				xx *= 10;
			tradata *= xx;
		}
	}
	else
	{
		len-=dotlen+1;
		if(dot > len)  //输入小数位不够
		{
			dot -= len;
			xx = 1;
			for(i=0;i<dot;i++)
				xx *= 10;
			tradata *= xx;
		}
		else if(dot < len) //输入小数位大于需要的，则除去
		{
			len -= dot;
			xx = 1;
			for(i=0;i<len;i++)
				xx *= 10;
			tradata /= xx;
			
		}
	}
	return tradata;

}

/*********************************************************************************************************
** Function name:           ASCII_To_HEX_Password	   
** Descriptions:            系统参数初始化	
** input parameters:        len　数据长度
                            dot　小数点位数返回
** output parameters:       无      
** Returned value:          无 
*********************************************************************************************************/

uint32_t ASCII_To_HEX_Password(uint8_t type,uint8_t *data,uint8_t len,uint8_t *dotcnt)
{
	uint8_t i,cnt=0;
	uint32_t tradata=0;
		if(len>8)
			return tradata;
		for(i=0;i<len;i++)
		{
			if((*(data+i)>=0x30&&*(data+i)<=0x39)||(*(data+i)==0x2e))
			{
				if(*(data+i)!=0x2e)
				{
					tradata *=10;
					tradata +=(*(data+i)-0x30);
				}
				else
					cnt++;
			}
			else 
				return 0;
		}
		if(cnt>1) 
			return 0;

	return tradata;
	
}



/***********************************************************************************************
* Function		: HextoAscii
* Description	: 16进制数转换为ASCII码
* Input			: 
* Output		: 
* Note(s)		: 注意，转化的ascii数组最多是十个字节
***********************************************************************************************/
void  HEX_TO_ASCII(uint32_t hexdata,uint8_t *data)
{
	uint32_t temp[10]={0};
	uint32_t hex;
	uint8_t i,j,k;
	uint32_t chushu=10;
	hex=hexdata	;
	if(hex<0xffffffff)
	{
		for(i=0;i<10;i++)
		{
			chushu=10;
			if(i==9)
			{
				for(j=0;j<i-1;j++)
					chushu*=10;
			    temp[9-i] = hex/chushu;
				temp[9-i]+='0';	
			}
			else
			{				
				for(j=0;j<i;j++)
					chushu*=10;
				temp[9-i] = hex%((uint32_t)chushu);
				hex-=temp[9-i];
				for(k=0;k<i;k++)
					temp[9-i]=temp[9-i]/10;
				temp[9-i]+='0';
			}
		}
	}
	for(i=0;i<10;i++)
		data[i]=(uint8_t)temp[i];
}


/**************************************************************************************************
**	函数名称:	MODBUS_CRC()
**	功	能	:	CRC16计算
**	入口参数:	*pc		:	指向计算数据的指针
**				  Length	：	数据队列的长度
**	出口参数:	
**  返回值  ： 	计算出的CRC16的值
**************************************************************************************************/
// 	crc16校验码计算函数,计算算法：
// 1、设置crc校验寄存器的初值为0xffff;
// 2、将报文的第一个字节与crc寄存器的低字节异或，结果存入crc寄存器
// 3、判断crc的第一位是否为1，如果是1,crc右移1位后和0xa001异或，如果为0，则再移1位；
// 4、重复步骤3，直到完成8个位；
// 5、重复步骤2、3、4直到完成所有字节
// 6、返回计算结果

uint16_t MODBUS_CRC(uint8_t *chData,unsigned short uNo)
{
			uint16_t crc=0xffff;
			uint16_t i,j;
			for(i=0;i<uNo;i++)
			{
						crc^=chData[i];                   //异或
						for(j=0;j<8;j++)
						{
									if(crc&1)
									{
												crc>>=1;
												crc^=0xA001;
									}
									else
												crc>>=1;
						}
			}
			return (crc);
}

/*********************************************************************************************************
ACS数据帧转换成HEX数组(限0-f数字码)
*********************************************************************************************************/
void AscToHexStr(uint8_t *ASCbuf,uint8_t *HEXbuf,uint8_t len)
{
	unsigned int i;
	
	for(i=0;i<len/2;i++)	{
		if(*(ASCbuf+2*i)>='a')
	  	*(HEXbuf+i) = ((*(ASCbuf+2*i)-'a'+10)<<4) + (*(ASCbuf+2*i+1)-'a'+10);   //a-f
		else
	  	*(HEXbuf+i) = ((*(ASCbuf+2*i)-'0')<<4) + (*(ASCbuf+2*i+1)-'0');         //0-9
	}
}

/*********************************************************************************************************
HEX数组转换成ACS数据帧
*********************************************************************************************************/
void HexToAscStr(uint8_t *HEXbuf,uint8_t *ASCbuf,uint8_t len)
{
	unsigned int i;
#if 0   //限BCD数字码
		for(i=0;i<len*2;i+=2)	{	  
			*(ASCbuf+i)   = (*(HEXbuf+i/2)>>4) + '0';
			*(ASCbuf+i+1) = (*(HEXbuf+i/2)%16)  + '0';			
	}	
#else   //限BCD数字码和字母
	unsigned char tmp;
	for(i=0;i<len;i++)
	{
		tmp = *(HEXbuf+i)>>4;
		if(tmp>=10)
			*(ASCbuf+i*2) = tmp-10+'a';      //字母
		else
			*(ASCbuf+i*2) = tmp+'0';         //数字
		
		tmp = *(HEXbuf+i)&0x0f;          
		if(tmp>=10) 
			*(ASCbuf+i*2+1) = tmp-10+'a';    //字母
		else 
			*(ASCbuf+i*2+1) = tmp+'0';       //数字
	}
#endif
		
	
}

