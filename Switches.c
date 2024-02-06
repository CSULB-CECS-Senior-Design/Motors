#include "Switches.h"
void switch_init(void){
if ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;	// Activate F clocks
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0){};
	}
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; 	// unlock GPIO Port F	
	//Switches
	GPIO_PORTF_CR_R |= 0x11;			// allow changes to PF4-0
	GPIO_PORTF_AMSEL_R &= ~0x11;		// disable analog on PF4-0
	GPIO_PORTF_PCTL_R &= ~0x000F000F;	// PCTL GPIO on PF4-0
	GPIO_PORTF_DIR_R &= ~0x11;			// PF4,PF0 in, PF3-1 out
	GPIO_PORTF_AFSEL_R &= ~0x11;		// disable alt funct on PF4-0
	GPIO_PORTF_PUR_R |= 0x11;			// enable pull-up on PF0 and PF4
	GPIO_PORTF_DEN_R |= 0x1F;			// enable digital I/O on PF4-0
	GPIO_PORTF_IS_R &= ~0x11;			// PF4,PF0 is edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x11;			// PF4,PF0 is not both edges
	GPIO_PORTF_IEV_R &= ~0x11;			// PF4,PF0 falling edge event
	GPIO_PORTF_ICR_R = 0x11;			// clear flag0,4
	GPIO_PORTF_IM_R |= 0x11;			// enable interrupt on PF0,PF4
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF1FFFFF)|0x00400000; // (g) bits:23-21 for PORTF, set priority to 2
	NVIC_EN0_R |= 0x40000000;			// (h) enable interrupt 30 in NVIC
}