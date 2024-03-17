#ifndef SPI_H
#define SPI_H

#include "tm4c123gh6pm.h"
#include <stdint.h>
void SPI_master_init(void);
void SPI_transmit(char data);
//uint16_t SPI_recieve(uint16_t code);
#endif