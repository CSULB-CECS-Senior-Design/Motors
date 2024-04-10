#ifndef SPI_H
#define SPI_H

#include "LED.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

void SPI_slave_init(void);
void SPI_receive(unsigned char *receive);
void SPI_transmit(unsigned char data);

#endif
