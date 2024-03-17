#include "tm4c123gh6pm.h"
#include "MotorSetup.h"
#include "MotorControl.h"
#include "PLL.h"
#include "LED.h"
#include "Switches.h"
#include "SPI.h"
#include <stdint.h>

void SPI_slave_init(void){
	SYSCTL_RCGCSSI_R |=	0x04; //Enable and provide a clock to SSI module 2 in Run mode.
	SYSCTL_RCGCGPIO_R |= 0x02; //Enable and provide a clock to GPIO Port B in run mode
	GPIO_PORTB_AFSEL_R |= 0xF0;//enable alt funct on PB4-7
	GPIO_PORTB_DEN_R |= 0xF0; //enable digital I/O on PB4-7
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0x0000FFFF)+0x22220000;	// enable digital I/O on PB 4-7
	GPIO_PORTB_AMSEL_R &= ~0xF0;          // disable analog functionality on PB 4-7
	SSI2_CR1_R &= ~SSI_CR1_SSE; //ensure SSE bit in SSICR1 is clear before any config changes
	SSI2_CR1_R |= SSI_CR1_MS;	//enable master mode
	SSI2_CC_R = (SSI2_CC_R&~SSI_CC_CS_M)+SSI_CC_CS_SYSPLL;	// clock divider for 3.33 MHz SSIClk 50/(24*(1+0)) = 2.08 MHz
	SSI2_CPSR_R = (SSI2_CPSR_R&~SSI_CPSR_CPSDVSR_M)+24;  //// must be even number
	SSI2_CR0_R &= ~(SSI_CR0_SCR_M | SSI_CR0_SPH | SSI_CR0_SPO);	// SPO = 0 // SCR = 0 (2.08 Mbps data rate)
	SSI2_CR0_R = (SSI2_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;	// DSS = 8-bit data
	SSI2_CR0_R = (SSI2_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8;
	SSI2_CR1_R |= SSI_CR1_SSE;            // enable SSI
}

void SPI_receive(char *receive){
	while((SSI2_SR_R&0x00000004)==0){};// SSI Recieve FIFO Not Empty
	*receive = SSI2_DR_R;               // acknowledge response
}
