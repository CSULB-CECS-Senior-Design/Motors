#include "tm4c123gh6pm.h"
#include "MotorSetup.h"
#include "MotorControl.h"
#include "PLL.h"
#include "LED.h"
#include "Switches.h"
#include "SPI.h"

#define LEFTPOWER	0.50*PERIOD
#define RIGHTPOWER	0.50*PERIOD

// basic functions defined at end of startup.s
extern void DisableInterrupts(void); // Disable interrupts
extern void WaitForInterrupt(void);  // low power mode
extern void EnableInterrupts(void);  // Enable interrupts
//unsigned char transmitData;
void GPIOPortF_Handler(void);
void delay_1ms(void);
void delay_2s(void);
void system_init();
unsigned char receivedData;
unsigned char transmitData;
int main(void){
	DisableInterrupts();
	system_init();
	EnableInterrupts();
	while(1){
		SPI_receive(&receivedData);
			switch(receivedData){
				case 'F':
					move_forward();
					transmitData = 'F';
					break;
				case 'B':
					move_backward();
					transmitData = 'B';
					break;
				case 'L':
					turn_left();
					transmitData = 'L';
					break;
				case 'R':
					turn_right();
					transmitData = 'R';
					break;
				case 'P':
					pivot_right();
					transmitData = 'P';
					break;
				case 'Q':
					pivot_left();
					transmitData = 'Q';
					break;			
				case 'S':
					stop_motors();
					transmitData = 'S';
					break;
				default:
					stop_motors();
					break;
			}
			SPI_transmit(transmitData);
	}
}

//System Initializations
void system_init(){
	motors_init();
	PLL_Init();
	led_init();
	SPI_slave_init();
	switch_init();
}

// Switch Interrupt Handler
void GPIOPortF_Handler(void){ 
	if(GPIO_PORTF_RIS_R&SW2){  // SW2 pressed
    GPIO_PORTF_ICR_R = SW2;  // acknowledge flag
		pwm_duty(LEFTPOWER, RIGHTPOWER);
		delay_1ms();
		}
	if(GPIO_PORTF_RIS_R&SW1){  // SW1 pressed
    GPIO_PORTF_ICR_R = SW1;  // acknowledge flag
		pwm_duty(LEFTPOWER, RIGHTPOWER);
		move_forward();
		delay_1ms();
  }
}

// 1ms Delay
void delay_1ms(void){
	unsigned long volatile time;
  time = 727240*100/91;  // 0.01sec
  while(time){
		time--;
  }
}

// 1ms Delay
void delay_2s(void){
	unsigned long volatile time;
  time = (727240*100/91) *2000;  // 0.01sec
  while(time){
		time--;
  }
}