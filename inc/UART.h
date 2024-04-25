#ifndef UART_H
#define UART_H

#include "stdint.h"

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

void UART1_Init(void);
void UART1_OutChar(char data);
void UART1_OutString(char *pt);
void UART1_OutUDec(uint16_t n);

#endif