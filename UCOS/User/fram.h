#ifndef __FRAM_H_
#define __FRAM_H_
#include "LPC177x_8x.h"
#include "lpc_types.h"
#include "system_LPC177x_8x.h"
#include <ucos_ii.h>
#include <ssp.h>
#include <gpio.h>
#include <print.h>
/******************************************
*    FRAMÃüÁî²Ù×÷Âë
*******************************************/
#define  CMD_FRAM_WR_ENABLE				0x06     //ÉèÖÃÐ´Ê¹ÄÜËø´æÆ÷
#define  CMD_FRAM_WR_DISABLE			0x04     //Ð´½ûÖ¹
#define  CMD_FRAM_RD_STATUS				0x05     //¶Á×´Ì¬¼Ä´æÆ÷
#define  CMD_FRAM_WR_STATUS				0x01     //Ð´×´Ì¬¼Ä´æÆ÷
#define  CMD_FRAM_RD_MEMORY				0x03     //¶Á´æ´¢Æ÷Êý¾Ý
#define  CMD_FRAM_WR_MEMORY				0x02     //Ð´´æ´¢Æ÷Êý¾Ý

#define 	SYS_PARA_ADDR 	  	  0x0000 		 //ÏµÍ³²ÎÊý´æ´¢µØÖ·

extern void	FramRead(uint8_t *dataptr,uint16_t addr,uint16_t length);
extern void FramWrite(uint8_t *dataptr,uint16_t addr,uint16_t length);

#endif
