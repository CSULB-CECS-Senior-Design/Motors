# Motors

## Project Overview
The R2 ARC project focuses on developing autonomous movement capabilities in robotics using advanced sensor integration and motor control techniques. This repo showcases the implementation of DC motors, IR sensors, and SPI communication to enable a machine to travel autonomously.

## Components
- **Motors**: 2x 12V Geartisian DC Motors (20 RPM)
- **Motor Driver**: L298N
- **Sensors**: 2x Sharp IR GP2Y0A21YK0F
- **Microcontrollers**: TM4C123GH6PM (as SPI slave)
- **Single Board Computers**:Raspberry Pi (as SPI master)

## Features
- **Motor Movement Control**: Implemented on TM4C microcontroller to handle precise movements.
- **SPI Communication**: Setup between TM4C (slave) and the main SBC (Raspberry Pi as master) to transmit motor commands and sensor data using unsigned 16-bit integers.
- **IR Sensors**: Utilized to enhance machine vision, aiding in autonomous navigation. Sensor data are transmitted to the main SBC via SPI.

## Branches
- **main**: Core codebase for the TM4C microcontroller, handling motor movements, SPI communication setup, and IR sensor integration.
- **Raspberry_Pi_Motor_Control**: Implementation of DC motor movements on the Raspberry Pi.
- **SPI_Communication_Slave_TM4C**: Branch for verifying TM4C's functionality as an SPI slave.
- **SPI_Communication_Master_TM4C**: Tests and setups for TM4C acting as an SPI master.
- **SPI_Communication_RaspberryPi_Master**: Implementation of SPI Master modules, initially in C++ and later in Python.
- **SensorTesting**: Branch dedicated to testing and calibrating IR sensors for optimized autonomous navigation.

## Setup and Installation
Ensure you have all the necessary hardware components connected as described in the hardware setup documentation. Follow the installation guides for each component before running the software.

## Contact
Contact Jesus perez for any questions at jesus.perez.cecs@gmail.com
