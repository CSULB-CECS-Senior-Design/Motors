#ifndef SPI_H
#define SPI_H

#include "LED.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
void SPI_slave_init(void);
void SPI_master_init(void);
void SPI_transmit(uint8_t data);


#endif