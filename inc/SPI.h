#ifndef SPI_H
#define SPI_H

#include "LED.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

void SPI_slave_init(void);
void SPI_receive(uint16_t *receive);
void SPI_transmit_word(uint16_t sensorValue);

#endif
