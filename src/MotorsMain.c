#include "tm4c123gh6pm.h"
#include "MotorSetup.h"
#include "MotorControl.h"
#include "PLL.h"
#include "LED.h"
#include "Switches.h"
#include "SPI.h"
#include "Sensors.h"

#define LEFTPOWER	0.60*PERIOD
#define RIGHTPOWER	0.60*PERIOD

// basic functions defined at end of startup.s
extern void DisableInterrupts(void); // Disable interrupts
extern void WaitForInterrupt(void);  // low power mode
extern void EnableInterrupts(void);  // Enable interrupts

void GPIOPortF_Handler(void);
void system_init();
void steering(uint16_t ahead_dist,uint16_t behind_dist);
uint16_t receivedData;

int main(void) {
	uint16_t ahead, behind;
	DisableInterrupts();
	system_init();
	EnableInterrupts();
	for(int x = 0; x < 10; x++){
		ReadSensorsFIRFilter(&ahead, &behind);//sensor test
	}
		while(1) {
			ReadSensorsFIRFilter(&ahead, &behind);	// Read sensor values
			uint8_t frontDistance = convert_to_centimeter(ahead);
			uint8_t backDistance = convert_to_centimeter(behind);
			uint16_t transmitData = encode_distance(frontDistance, backDistance);
			SPI_receive(&receivedData);
			switch(receivedData){
				case 'W':
					pwm_duty(LEFTPOWER, RIGHTPOWER);
					move_forward();
					break;
				case 'S':
					pwm_duty(LEFTPOWER, RIGHTPOWER);
					move_backward();
					break;
				case 'A':
					pwm_duty(LEFTPOWER, RIGHTPOWER);
					turn_left();
					break;
				case 'D':
					pwm_duty(LEFTPOWER, RIGHTPOWER);
					turn_right();
					break;
				case 'P':
					pwm_duty(LEFTPOWER, RIGHTPOWER);
					pivot_right();
					break;
				case 'O':
					pwm_duty(LEFTPOWER, RIGHTPOWER);
					pivot_left();
					break;
				case 'Q':
					stop_motors();
					break;
				default:
					stop_motors();
					break;
			}
			SPI_transmit_word(transmitData);
		}
}

//System Initializations
void system_init() {
	motors_init();
	PLL_Init();
	led_init();
	SPI_slave_init();
	switch_init();
	Sensors_Init();
}

// Switch Interrupt Handler
void GPIOPortF_Handler(void) { 
	if(GPIO_PORTF_RIS_R&SW2) {	// SW2 pressed
		GPIO_PORTF_ICR_R = SW2;	// acknowledge flag
		pwm_duty(LEFTPOWER, RIGHTPOWER);
		stop_motors();			// Emergency stop
	}
	if(GPIO_PORTF_RIS_R&SW1) {	// SW1 pressed
		GPIO_PORTF_ICR_R = SW1;	// acknowledge flag
		pwm_duty(LEFTPOWER, RIGHTPOWER);
		move_forward();
	}
}
