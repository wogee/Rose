#ifndef __INSULATION_H_
#define __INSULATION_H_
#include "LPC177x_8x.h"
#include "lpc_types.h"
#include "system_LPC177x_8x.h"
#include <ucos_ii.h>

extern uint8_t InsulationFlag;
extern uint8_t OutVoltageDetFlag;

extern uint32_t  InsulationResistorOne ;		 //¾øÔµ¼ì²âµç×è1
extern uint32_t  InsulationResistorTwo ;		 //¾øÔµ¼ì²âµç×è2
extern uint32_t  InsuVoltage;                //¾øÔµ¼ì²â²âÁ¿µçÑ¹

extern void InsulationMain (void);





#endif
