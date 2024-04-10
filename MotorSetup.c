#include "MotorSetup.h"

#define SPEED_STEP	PERIOD * 0.1
uint64_t currDuty;

void left_motor_init(void);
void right_motor_init(void);
void motor_direction_init(void);

void motors_init(void) {
	right_motor_init();			// PB6/M0PWM0
	left_motor_init();			// PB7/M0PWM1
	motor_direction_init();		// DIR/SLP motor pins on GPIOPortE
}

// Output on PB7/M0PWM1 left motor
void left_motor_init(void)	{
	SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
	SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
	GPIO_PORTB_AFSEL_R |= 0x80;           // enable alt funct on PB7
	GPIO_PORTB_PCTL_R &= ~0xF0000000;     // configure PB7 as M0PWM1
	GPIO_PORTB_PCTL_R |= 0x40000000;
	GPIO_PORTB_AMSEL_R &= ~0x80;          // disable analog functionality on PB7
	GPIO_PORTB_DEN_R |= 0x80;             // enable digital I/O on PB7
	SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV; // 3) use PWM divider
	SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M; //    clear PWM divider field
	SYSCTL_RCC_R += SYSCTL_RCC_PWMDIV_2;  //    configure for /2 divider
	PWM0_0_CTL_R = 0;                     // 4) re-loading down-counting mode
	PWM0_0_GENB_R = (PWM_0_GENB_ACTCMPBD_ONE|PWM_0_GENB_ACTLOAD_ZERO); // 0xC08
	// PB7 goes low on LOAD
	// PB7 goes high on CMPB down
	PWM0_0_LOAD_R = PERIOD - 1;           // 5) cycles needed to count down to 0: LAB2: PF1->M1PWM5:PWM1_2_
	PWM0_0_CMPB_R = 0;             				// 6) count value when output rises: Lab 2:5%2=1->CMPB, GENB
	PWM0_0_CTL_R |= 0x00000001;           // 7) start PWM0: odd->B, even->A
	PWM0_ENABLE_R |= 0x00000002;          // enable PB7/M0PWM1
}

// Output on PB6/M0PWM0 right motor
void right_motor_init(void) {
	SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
	SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B: 000010
	while((SYSCTL_RCGCGPIO_R&0x02) == 0);
	GPIO_PORTB_AFSEL_R |= 0x40;           // enable alt funct on PB6: 0100 0000
	GPIO_PORTB_PCTL_R &= ~0x0F000000;     // configure PB6 as PWM0
	GPIO_PORTB_PCTL_R |= 0x04000000;
	GPIO_PORTB_AMSEL_R &= ~0x40;          // disable analog functionality on PB6
	GPIO_PORTB_DEN_R |= 0x40;             // enable digital I/O on PB6
	GPIO_PORTB_DR8R_R |= 0xC0;    		  // enable 8 mA drive on PB6,7
	SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
	(SYSCTL_RCC_R & (~0x001E0000));   	  //    configure for /2 divider: PWM clock: 80Mhz/2=40MHz
	PWM0_0_CTL_R = 0;                     // 4) re-loading down-counting mode
	PWM0_0_GENA_R = 0xC8;                 // low on LOAD, high on CMPA down
	// PB6 goes low on LOAD
	// PB6 goes high on CMPA down
	PWM0_0_LOAD_R = PERIOD - 1;           // 5) cycles needed to count down to 0
	PWM0_0_CMPA_R = 0;             		  // 6) count value when output rises
	PWM0_0_CTL_R |= 0x00000001;           // 7) start PWM0
	PWM0_ENABLE_R |= 0x00000001;          // enable PB6/M0PWM0
}

// Subroutine to initialize port E pins PE0-3 for use with L298N Motor Driver direction
// PE0-3 control direction of motor
void motor_direction_init(void) {
	if ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOB)==0) {
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;	// Activate B clocks
		while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOB)==0){};
	}
	GPIO_PORTB_AMSEL_R &= ~0x3C;		// disable analog function
	GPIO_PORTB_AFSEL_R &= ~0x3C;		// no alternate function
  	GPIO_PORTB_PCTL_R &= ~0x00FFFF00;	// GPIO clear bit PCTL 
	GPIO_PORTB_DIR_R |= 0x3C; 			// output on pin(s)
  	GPIO_PORTB_DEN_R |= 0x3C;			// enable digital I/O on pin(s)
}

// Duty is number of PWM clock cycles output is high  
void pwm_duty(unsigned long dutyL, unsigned long dutyR) {
	PWM0_0_CMPA_R = dutyR - 1;	// PB6 right motor
	PWM0_0_CMPB_R = dutyL - 1;	// PB7 left motor
}

// Get Current Duty Cycle
unsigned long get_current_duty(void) {
	return currDuty;
}