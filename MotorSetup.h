#ifndef MOTORSETUP_H
#define	MOTORSETUP_H

//Define Motor pin constants
extern const int ENA;	//DC Motor 1 PWM 0
extern const int IN1;	//DC Motor 1 Input A
extern const int IN2;	//DC Motor 1 Input B
extern const int IN3;	//DC Motor 2 Input A
extern const int IN4;   //DC Motor 2 Input B
extern const int ENB;	//DC Motor 2 PWM 1

//Motor Setup Functions
void motors_init();
void pwm_init();
void start_motors();
void stop_motors();

#endif	//MOTORSETUP_H_H
