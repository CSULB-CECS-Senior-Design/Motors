#include <iostream>
#include <pigpio.h>
#include "MotorSetup.h"

// Foward Movement, both wheels fowards
void move_forward() {
	stop_motors();	//Stop Motors
	start_motors();	//Start Motors
}

// Backwards Movement, both wheels backwards
void move_backwards() {
	gpioPWM(ENA, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN1, 0);    //Set DC Motor A IN1 Low
	gpioWrite(IN2, 1);	  //Set DC Motor A IN2 High
	gpioPWM(ENB, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN3, 0);    //Set DC Motor B IN3 Low
	gpioWrite(IN4, 1);	  //Set DC Motor B IN1 High
}

// Turn Left, right wheel foward on and left wheel off
void turn_left() {
	gpioPWM(ENA, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN1, 0);    //Set DC Motor A IN1 Low
	gpioWrite(IN2, 0);	  //Set DC Motor A IN2 Low
	gpioPWM(ENB, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN3, 1);    //Set DC Motor B IN3 High
	gpioWrite(IN4, 0);	  //Set DC Motor B IN1 Low
}

// Turn Right, left wheel foward and right wheel off
void turn_right() {		  
	gpioPWM(ENA, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN1, 1);    //Set DC Motor A IN1 High
	gpioWrite(IN2, 0);	  //Set DC Motor A IN2 Low
	gpioPWM(ENB, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN3, 0);    //Set DC Motor B IN3 Low
	gpioWrite(IN4, 0);	  //Set DC Motor B IN1 Low
}

// Left Pivot, right wheel fowards and left wheel backwards
void pivot_left() {
	gpioPWM(ENA, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN1, 0);    //Set DC Motor A IN1 Low
	gpioWrite(IN2, 1);	  //Set DC Motor A IN2 High
	gpioPWM(ENB, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN3, 1);    //Set DC Motor B IN3 high
	gpioWrite(IN4, 0);	  //Set DC Motor B IN1 low
}

//Right Pivot, left wheel fowards and right wheel backwards
void pivot_right() {
	gpioPWM(ENA, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN1, 1);    //Set DC Motor A IN1 High
	gpioWrite(IN2, 0);	  //Set DC Motor A IN2 Low
	gpioPWM(ENB, 205);    //205 out of 255 for 80% duty cycle
	gpioWrite(IN3, 0);    //Set DC Motor B IN3 Low
	gpioWrite(IN4, 1);	  //Set DC Motor B IN1 High
}



