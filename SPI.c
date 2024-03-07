#include "tm4c123gh6pm.h"
#include <stdint.h>

void SPI_slave_init(void){
	SYSCTL_RCGCSSI_R |=	0x01; //Enable and provide a clock to SSI module 0 in Run mode.
	SYSCTL_RCGCGPIO_R |= 0x01; //Enable and provide a clock to GPIO Port A in Run mode
	while((SYSCTL_PRGPIO_R&0x01) == 0){}; //wait for ready
	GPIO_PORTA_AFSEL_R |= 0x3C; //enable alt funct on PA2-5
	GPIO_PORTA_PCTL_R |= 0x00222200;	// enable digital I/O on PA 2-5
	GPIO_PORTA_DEN_R |= 0x3C; //enable digital I/O on PA2-5
	GPIO_PORTA_DIR_R &= ~0x08; // Set PA3 as input
	SSI0_CR1_R &= ~0x00000010; //ensure SSE bit in SSICR1 is clear before any config changes
	SSI0_CR1_R = 0x00000004;	//enable slave mode
	SSI0_CC_R = 0x00; //use system clock
	SSI0_CPSR_R = 8; //CPSDVSR number 16Mhz/8*(1+0)
	SSI0_CR0_R = 0x07; //Freescale SPI Mode, 1mbps , 8 data bits
	SSI0_CR1_R |= 0x00000010; //set SSE bit and enable SPI
}

void SPI_master_init(void){
	SYSCTL_RCGCSSI_R |=	0x00000100; //Enable and provide a clock to SSI module 2 in Run mode.
	SYSCTL_RCGCGPIO_R |= 0x02; //Enable and provide a clock to GPIO Port B in run mode
	while((SYSCTL_PRGPIO_R&0x00000100) == 0){};
	GPIO_PORTB_AFSEL_R |= 0xF0;//enable alt funct on PB4-7
	GPIO_PORTB_PCTL_R |= 0x22220000;	// enable digital I/O on PB 4-7
	GPIO_PORTB_DEN_R |= 0xF0; //enable digital I/O on PB4-7
	GPIO_PORTB_DIR_R &= ~0x20; // Set PB5 as input
	SSI2_CR1_R &= ~0x00000010; //ensure SSE bit in SSICR1 is clear before any config changes
	SSI2_CR1_R = 0x00000000;	//enable master mode
	SSI2_CC_R = 0x00; //use system clock
	SSI2_CPSR_R = 8; //CPSDVSR number 16Mhz/8*(1+0)
	SSI2_CR0_R = 0x07; //Freescale SPI Mode, 1mbps , 8 data bits
	SSI2_CR1_R |= 0x00000010; //set SSE bit and enable SPI
}


void SPI_transmit(uint8_t data){
  while((SSI0_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI0_DR_R = data; // data out, no reply
}
