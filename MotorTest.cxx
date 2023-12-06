#include <iostream>
#include <pigpio.h>
#include "MotorSetup.h"
#include "MotorControl.h"

int main() {
	//Initialize GPIO library. Print out an error if initialization fails
	if (gpioInitialise() < 0) {
		std::cerr << "pigpio initialization failed" << std::endl;
		return 1;
	}
	motors_init();        //Initialize Motor Configurations
	pwm_init();       	  //Initialize PWM Configurations	
	char userInput;       // Declare character to take user input
	bool exit = false;    //Declare boolean to exit case statements
	
	//Loop will run until user decides to exit
	while(!exit){
		std::cout << "Enter Command: f: forward, b: backwards, l:left, r:right, q:left pivot, p:right pivot, z: exit program"; std::cin >> userInput;
		// Stop Motors before executing a command
		stop_motors();
		//Process the user input
		switch(userInput) {
			//User inputs 'f' to move DC Motors forward
			case 'f':
				move_forward();
				break;
			//User inputs 'b' to move DC Motors backwards
			case 'b':
				move_backwards();
				break;
			//User inputs 'l' to move DC Motors left	
			case 'l':
				turn_left();
				break;
			//User inputs 'r' to move DC Motors right
			case 'r':
				turn_right();
				break;
			//User inputs 'q' to make DC motors Pivot left
			case 'q':
				pivot_left();
				break;
			//User inputs 'p' to make DC motors Pivot right
			case 'p':
				pivot_right();
				break;
			//User inputs 'z' to exit the program
			case 'z':
				exit = true;
				break;
			//Handle invalid input	
			default:
			std::cout << "Invalid Command" << std::endl;
		}
	}
	stop_motors();      //Ensure Motors are stopped before exiting program
	gpioTerminate();    //Terminate GPIO Resources
	return 0; 			
}

