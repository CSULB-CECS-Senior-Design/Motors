#include "tm4c123gh6pm.h"
#include "UART.h"
#include "stdint.h"
//------------UART_Init------------
// Initialize the UART for 57600 baud rate (assuming 16 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART1_Init(void){
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
	UART1_CTL_R = 0;						// disable UART
	UART1_IBRD_R = 17;						// IBRD = int(16,000,000 / (16 * 57600)) = int(17.3611)
	UART1_FBRD_R = 23;						// FBRD = int(0.3611 * 64 + 0.5) = 23
											// 8 bit word length (no parity bits, one stop bit, FIFOs)
	UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
	UART1_CTL_R |= UART_CTL_RXE|UART_CTL_TXE|UART_CTL_UARTEN;// enable Tx, RX and UART
	GPIO_PORTB_AFSEL_R |= 0x03;				// enable alt funct on PB1-0
	GPIO_PORTB_DEN_R |= 0x03;				// enable digital I/O on PB1-0
											// configure PA1-0 as UART
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;
	GPIO_PORTB_AMSEL_R &= ~0x03;			// disable analog functionality on PA
}

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART1_OutChar(char data){
	while((UART0_FR_R&UART_FR_TXFF) != 0);
	UART1_DR_R = data;
}

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART1_OutString(char *pt){
	while(*pt){
		UART1_OutChar(*pt);
		pt++;
	}
	//UART0_OutChar(0); // add the null terminator
}

//-----------------------UART_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1-10 digits with no space before or after
void UART1_OutUDec(uint16_t n) {
	// This function uses recursion to convert decimal number
	//   of unspecified length as an ASCII string
	if(n >= 10) {
		UART1_OutUDec(n/10);
		n = n%10;
	}
	UART1_OutChar(n+'0'); /* n is between 0 and 9 */
}