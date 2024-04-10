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
		move_forward();
		SPI_receive(&receivedData);
			switch(receivedData){
				case 'W':
					move_forward();
					transmitData = 'W';
					break;
				case 'S':
					move_backward();
					transmitData = 'S';
					break;
				case 'A':
					turn_left();
					transmitData = 'A';
					break;
				case 'D':
					turn_right();
					transmitData = 'D';
					break;
				case 'P':
					pivot_right();
					transmitData = 'P';
					break;
				case 'O':
					pivot_left();
					transmitData = 'O';
					break;			
				case 'Q':
					stop_motors();
					transmitData = 'Q';
					break;
				default:
					stop_motors();
					break;
			}
		//	delay_1ms();
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