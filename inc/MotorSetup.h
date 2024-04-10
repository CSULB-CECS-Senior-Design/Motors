#ifndef MOTORSETUP_H
#define MOTORSETUP_H

#define STOP        1
#define MAX_SPEED   PERIOD - 1
#define HALF_SPEED	PERIOD * 0.5

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "PLL.h"

void motors_init(void);
void pwm_duty(unsigned long dutyL, unsigned long dutyR);
unsigned long get_current_duty(void);

#endif
