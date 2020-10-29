#ifndef __GPIO_H_
#define __GPIO_H_
#include "LPC177x_8x.h"
#include "lpc_types.h"

#define SYSLED        	(1ul << 6)                             	 			                     
#define SYSLED_ON()   	LPC_GPIO2->DIR |= SYSLED; LPC_GPIO2->SET |= SYSLED     				 
#define SYSLED_OFF()   	LPC_GPIO2->DIR |= SYSLED; LPC_GPIO2->CLR |= SYSLED

#define SE12V_SWITCH        	(1ul << 26)                             	 			                     
#define SE12V_SWITCH_ON()   	LPC_GPIO3->DIR |= SE12V_SWITCH; LPC_GPIO3->SET |= SE12V_SWITCH     				 
#define SE12V_SWITCH_OFF()    LPC_GPIO3->DIR |= SE12V_SWITCH; LPC_GPIO3->CLR |= SE12V_SWITCH

#define SE24V_SWITCH        	(1ul << 25)                             	 			                     
#define SE24V_SWITCH_ON()   	LPC_GPIO3->DIR |= SE24V_SWITCH; LPC_GPIO3->SET |= SE24V_SWITCH     				 
#define SE24V_SWITCH_OFF()    LPC_GPIO3->DIR |= SE24V_SWITCH; LPC_GPIO3->CLR |= SE24V_SWITCH

#define AC_SWITCH        	(1ul << 24)                             	 			                     
#define AC_SWITCH_ON()   	LPC_GPIO3->DIR |= AC_SWITCH; LPC_GPIO3->SET |= AC_SWITCH     				 
#define AC_SWITCH_OFF()   LPC_GPIO3->DIR |= AC_SWITCH; LPC_GPIO3->CLR |= AC_SWITCH

#define DC_SWITCH        	(1ul << 19)                             	 			                     
#define DC_SWITCH_ON()   	LPC_GPIO1->DIR |= DC_SWITCH; LPC_GPIO1->SET |= DC_SWITCH     				 
#define DC_SWITCH_OFF()   LPC_GPIO1->DIR |= DC_SWITCH; LPC_GPIO1->CLR |= DC_SWITCH

#define QDC_SWITCH        	(1ul << 19)                             	 			                     
#define QDC_SWITCH_ON()   	LPC_GPIO1->DIR |= QDC_SWITCH; LPC_GPIO1->SET |= QDC_SWITCH     				 
#define QDC_SWITCH_OFF()    LPC_GPIO1->DIR |= QDC_SWITCH; LPC_GPIO1->CLR |= QDC_SWITCH

#define LOCK_SWITCH        	(1ul << 11)                             	 			                     
#define LOCK_SWITCH_ON()   	LPC_GPIO2->DIR |= LOCK_SWITCH; LPC_GPIO2->SET |= LOCK_SWITCH     				 
#define LOCK_SWITCH_OFF()   LPC_GPIO2->DIR |= LOCK_SWITCH; LPC_GPIO2->CLR |= LOCK_SWITCH

#define FRAM_CS        	  (1ul << 16)                             	 			                     
#define FRAM_CS_H()   	 LPC_GPIO0->DIR |= FRAM_CS; LPC_GPIO0->SET |= FRAM_CS     				 
#define FRAM_CS_L()   	 LPC_GPIO0->DIR |= FRAM_CS; LPC_GPIO0->CLR |= FRAM_CS

#define WDT        	    (1ul << 27)                             	 			                     
#define WDT_ON()   	  	LPC_GPIO0->DIR |= WDT; LPC_GPIO0->SET |= WDT    				 
#define WDT_OFF()   	  LPC_GPIO0->DIR |= WDT; LPC_GPIO0->CLR |= WDT

#define EN485_U1        	    (1ul << 31) 
#define ENRD485_U1()   	LPC_GPIO4->DIR |= EN485_U1; LPC_GPIO4->SET |= EN485_U1            
#define ENWR485_U1() 		LPC_GPIO4->DIR |= EN485_U1; LPC_GPIO4->CLR |= EN485_U1   
 
#define EN485_U2        	    (1ul << 30) 
#define ENRD485_U2()   	LPC_GPIO4->DIR |= EN485_U2; LPC_GPIO4->SET |= EN485_U2            
#define ENWR485_U2() 		LPC_GPIO4->DIR |= EN485_U2; LPC_GPIO4->CLR |= EN485_U2  

#define CHARGERNO_INT       	          (1ul << 4) 
#define CHARGERNO_INT_Init()   	        (LPC_GPIO4->DIR &= ~STOP_INT)          
#define CHARGERNO_INT_Status() 	        (!(LPC_GPIO4->PIN & STOP_INT))

#define STOP_INT       	                (1ul << 24) 
#define STOP_INT_Init()   	            (LPC_GPIO1->DIR &= ~STOP_INT)          
#define STOP_INT_Status() 	            (!(LPC_GPIO1->PIN & STOP_INT))	           

#define DOOR_INT       	                (1ul << 25) 
#define DOOR_INT_Init()   	            (LPC_GPIO1->DIR &= ~DOOR_INT)          
#define DOOR_INT_Status() 	            (!(LPC_GPIO1->PIN & DOOR_INT))	      

#define LOCK_INT       	                (1ul << 26) 
#define LOCK_INT_Init()   	            (LPC_GPIO1->DIR &= ~LOCK_INT)            
#define LOCK_INT_Status() 	            (!(LPC_GPIO1->PIN & LOCK_INT))	       
 
#define TEMPswitch_INT       	          (1ul << 27) 
#define TEMPswitch_INT_Init()   	      (LPC_GPIO1->DIR &= ~TEMPswitch_INT)          
#define TEMPswitch_INT_Status() 	      (!(LPC_GPIO1->PIN & TEMPswitch_INT))	          

#define DCswitch_INT       	            (1ul << 28) 
#define DCswitch_INT_Init()   	        (LPC_GPIO1->DIR &= ~DCswitch_INT)          
#define DCswitch_INT_Status() 	        (!(LPC_GPIO1->PIN & DCswitch_INT))	         
 
#define INswitch_INT       	            (1ul << 4) 
#define INswitch_INT_Init()   	        (LPC_GPIO4->DIR &= ~INswitch_INT)           
#define INswitch_INT_Status() 	        (!(LPC_GPIO4->PIN & INswitch_INT))	      


extern void GPIOInit(void );










#endif

