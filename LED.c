#include "LED.h"

void led_init(void) {
	if ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0) {
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;		// Activate F clocks
		while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0){};
	}
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0);
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;			// unlock GPIO Port F
	GPIO_PORTF_CR_R |= RGB;					// allow changes to PF4-0
	GPIO_PORTF_AMSEL_R &= ~RGB;				// 3) disable analog function
	GPIO_PORTF_PCTL_R &= ~0x000FFFFF;			// 4) GPIO clear bit PCTL
	GPIO_PORTF_DIR_R |= RGB;				// 6) output logic
	GPIO_PORTF_AFSEL_R &= ~RGB;				// 7) no alternate function
	GPIO_PORTF_DEN_R |= RGB;				// 8) enable digital pins
	LED = Dark;						// Turn off all LEDs.
}
