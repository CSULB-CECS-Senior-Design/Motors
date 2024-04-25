#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "LED.h"
#include "tm4c123gh6pm.h"

void move_forward(void);
void move_backward(void);
void pivot_left(void);
void pivot_right(void);
void turn_left(void);
void turn_right(void);
void stop_motors(void);

#endif
