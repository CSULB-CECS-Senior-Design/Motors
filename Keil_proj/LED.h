#ifndef LED_H
#define LED_H

#define LED (*((volatile unsigned long *)0x40025038))  // use onboard three LEDs: PF321

#define	RGB				0x0E	// PF3, PF2, PF1
#define Dark    	0x00    //  ---
#define Red     	0x02    //  R--
#define Blue    	0x04    //  --B
#define Green   	0x08    //  -G-
#define Yellow  	0x0A    //  RG-
#define Cran      0x0C    //  -GB
#define White   	0x0E    //  RGB
#define Purple  	0x06    //  R-B

#include "tm4c123gh6pm.h"

void led_init(void);

#endif