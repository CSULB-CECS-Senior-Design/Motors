#include <iostream>
#include <pigpio.h>
#include "MotorSetup.h"

//GPIO Pins connected to the L298N Motor Driver
const int ENA = 18;	   //DC Motor 1 PWM 0
const int IN1 = 23;	   //DC Motor 1 Input A
const int IN2 = 24;	   //DC Motor 1 Input B
const int IN3 = 5;	   //DC Motor 2 Input A
const int IN4 = 6;     //DC Motor 2 Input B
const int ENB = 13;    //DC Motor 2 PWM 1

void motors_init() {
	//Set GPIO Motor pins as output
	gpioSetMode(ENA, PI_OUTPUT);	//Set PWM0 GPIO Pin 18 as output
	gpioSetMode(IN1, PI_OUTPUT);	//Set IN1 GPIO Pin 23 as output
	gpioSetMode(IN2, PI_OUTPUT);	//Set IN2 GPIO Pin 24 as output
	gpioSetMode(ENB, PI_OUTPUT);	//Set PWM1 GPIO Pin 13 as output
	gpioSetMode(IN1, PI_OUTPUT);	//Set IN3 GPIO Pin 5 as output
	gpioSetMode(IN2, PI_OUTPUT);	//Set IN4 GPIO Pin 6 as output
}

void pwm_init() {
	//Set PWM frequency
	gpioSetPWMfrequency(ENA, 2000);    //Set up Motor A to 2000 Hz PWM frequency
	gpioSetPWMfrequency(ENB, 2000);	   //Set up Motor B to 2000 Hz PWM frequency
}

void start_motors() {
	//Start both DC Motors
	gpioPWM(ENA, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN1, 1);    //Set DC Motor A IN1 High
	gpioWrite(IN2, 0);	  //Set DC Motor A IN2 Low
	gpioPWM(ENB, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN3, 1);    //Set DC Motor B IN3 High
	gpioWrite(IN4, 0);	  //Set DC Motor B IN1 Low
}

void stop_motors() {
	//Stop both DC Motors
	gpioPWM(ENA, 0);      //0 out of 255 for 0% duty cycle
	gpioWrite(IN1, 0);    //Set DC Motor A IN1 Low
	gpioWrite(IN2, 0);	  //Set DC Motor A IN2 Low
	gpioPWM(ENB, 0);      //0 out of 255 for 0% duty cycle
	gpioWrite(IN3, 0);    //Set DC Motor B IN3 Low
	gpioWrite(IN4, 0);	  //Set DC Motor B IN1 Low
}
