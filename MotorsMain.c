#include "tm4c123gh6pm.h"
#include "MotorSetup.h"
#include "MotorControl.h"
#include "PLL.h"
#include "LED.h"
#include "Switches.h"


#define LEFTPOWER	0.60*PERIOD
#define RIGHTPOWER	0.60*PERIOD

// basic functions defined at end of startup.s
extern void DisableInterrupts(void); // Disable interrupts
extern void WaitForInterrupt(void);  // low power mode
extern void EnableInterrupts(void);  // Enable interrupts


void GPIOPortF_Handler(void);
void delay_1ms(void);
void system_init();

int main(void){
	DisableInterrupts();
	system_init();
	EnableInterrupts();
	while(1){
		WaitForInterrupt();
			//pwm_duty(LEFTPOWER, RIGHTPOWER); // doesnt do anything i think
			//move_forward(); //right motor moves
	}
}

//System Initializations
void system_init(){
	motors_init();
	PLL_Init();
	led_init();
	switch_init();
}

// Switch Interrupt Handler
void GPIOPortF_Handler(void){ // 
  if(GPIO_PORTF_RIS_R&SW2){  // SW2 pressed
    GPIO_PORTF_ICR_R = SW2;  // acknowledge flag
		stop_motors();
		delay_1ms();
		}
	if(GPIO_PORTF_RIS_R&SW1){  // SW1 pressed
    GPIO_PORTF_ICR_R = SW1;  // acknowledge flag
		pwm_duty(LEFTPOWER, RIGHTPOWER);
		move_backward();	
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