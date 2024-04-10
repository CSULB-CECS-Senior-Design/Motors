#include "MotorControl.h"

#define DIRECTION	(*((volatile unsigned long *)0x4002403C))	// Mask for PE0-3
#define FORWARD 		0x0F	//1111
#define BACKWARD 		0x0A	//1010
#define LEFTPIVOT		0x09	//1001
#define RIGHTPIVOT		0x06	//0110
#define L_MOTOR			0x02	// M0PWM1
#define R_MOTOR			0x01	// M0PWM0

// Car movements
void move_forward(void) {
	LED = Green;
	DIRECTION = FORWARD;
	PWM0_ENABLE_R |= L_MOTOR;	// enable left wheel
	PWM0_ENABLE_R |= R_MOTOR;	// enable right wheel
}

void move_backward(void) {
	LED = Blue;
	DIRECTION = BACKWARD;
	PWM0_ENABLE_R |= L_MOTOR;	// enable left wheel
	PWM0_ENABLE_R |= R_MOTOR;	// enable right wheel
}

void pivot_left(void) {
	LED = Yellow;
	DIRECTION = LEFTPIVOT;
	PWM0_ENABLE_R |= L_MOTOR;	// enable left wheel
	PWM0_ENABLE_R |= R_MOTOR;	// enable right wheel
}

void pivot_right(void) {
	LED = Purple;
	DIRECTION = RIGHTPIVOT;
	PWM0_ENABLE_R |= L_MOTOR;	// enable left wheel
	PWM0_ENABLE_R |= R_MOTOR;	// enable right wheel
}

void turn_left(void) {
	LED = White;
	DIRECTION = FORWARD;
	PWM0_ENABLE_R &= ~L_MOTOR; 	// stop left wheel
	PWM0_ENABLE_R |= R_MOTOR; 	// enable right wheel
}

void turn_right(void) {
	LED = Cran;
	DIRECTION = FORWARD;
	PWM0_ENABLE_R |= L_MOTOR; 	// enable left wheel
	PWM0_ENABLE_R &= ~R_MOTOR; 	// stop right wheel
}

void stop_motors(void) {
	LED = Dark;
	PWM0_ENABLE_R &= ~L_MOTOR; 	// stop right wheel
	PWM0_ENABLE_R &= ~R_MOTOR; 	// stop left wheel
}
