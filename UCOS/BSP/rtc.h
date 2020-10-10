#ifndef __RTC_H_
#define __RTC_H_
#include "LPC177x_8x.h"
#include "lpc_types.h"
#include "system_LPC177x_8x.h"
#include <main.h>
#include <gpio.h>
#include <bms.h>

extern uint32_t ScnTime;
extern uint16_t InsulationTime;
extern uint32_t ChargedTime;

typedef struct _DATETime{
   uint8_t	second;
   uint8_t	minute;
   uint8_t	hour;
   uint8_t	day;
   uint8_t	week;
   uint8_t	month;
   uint16_t	year;
}DATETime;
extern  DATETime RTCtimedate;


extern void ExRTCSet(DATETime *pTimeAndDate );
extern uint32_t RTCInit (DATETime *pTimeAndDate );
extern uint32_t RTCInit (DATETime *pTimeAndDate );



#endif
