#include "tm4c123gh6pm.h"
#include "MotorSetup.h"
#include "MotorControl.h"
#include "PLL.h"
#include "LED.h"
#include "Switches.h"
#include "SPI.h"
#include <stdint.h>

void SPI_slave_init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_SSI0;  // activate SSI0
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
	delay = SYSCTL_RCGC2_R;               // allow time to finish activating
	GPIO_PORTA_AFSEL_R |= 0x3C; //enable alt funct on PA2-5
	GPIO_PORTA_DEN_R |= 0x3C; //enable digital I/O on PA2-5
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFF0F00FF)+0x00202200;
	GPIO_PORTA_AMSEL_R &= ~0x3C;          // disable analog functionality on PA2,3,5,6,7
	SSI0_CR1_R &= ~SSI_CR1_SSE;           // disable SSI
	SSI0_CR1_R |= SSI_CR1_MS;            	// slave mode
	SSI0_CC_R = (SSI0_CC_R&~SSI_CC_CS_M)+SSI_CC_CS_SYSPLL;			// clock divider for 3.33 MHz SSIClk 40/(8*(1+0)) = 5 MHz
	SSI0_CPSR_R = (SSI0_CPSR_R&~SSI_CPSR_CPSDVSR_M)+8;					// must be even number
	SSI0_CR0_R &= ~(SSI_CR0_SCR_M);//; |SSI_CR0_SPH | SSI_CR0_SPO);	// SPO = 0 // SCR = 0 (2.08 Mbps data rate)
	SSI0_CR0_R |= (SSI_CR0_SPO | SSI_CR0_SPH); // SPO = 1, SPH = 1
	SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;	// DSS = 8-bit data
	SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8;
	SSI0_CR1_R |= SSI_CR1_SSE;            // enable SSI
}

void SPI_receive(unsigned char *receive){
	while((SSI0_SR_R & SSI_SR_RNE) == 0);	// while the receive fifo is empty
	*receive = SSI0_DR_R ;//& 0xFF;      // acknowledge response
}

void SPI_transmit(unsigned char data){
  while((SSI0_SR_R & SSI_SR_TNF) == 0); // while transmit fifo full
	SSI0_DR_R = data; // command out
}

