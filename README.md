# Motors

## Project Overview
The R2 ARC project focuses on developing autonomous movement capabilities in robotics using advanced sensor integration and motor control techniques. This repository showcases the implementation of DC motors, IR sensors, and SPI communication within the R2 ARC

## Components
- **Motors**: 2x 12V Geartisian DC Motors (20 RPM)
- **Motor Driver**: L298N
- **Sensors**: 2x Sharp IR GP2Y0A21YK0F
- **Microcontrollers**: TM4C123GH6PM (as SPI slave)
- **Single Board Computers**:Raspberry Pi (as SPI master)

## Installation
Keil uVision 5 Setup
To develop and upload the firmware for the TM4C microcontroller, follow these steps:

1. Download and Install Keil uVision 5:

Download Keil uVision 5 from Keil's official website.
Follow the installation instructions provided on the website.

2. Open the Project:

Launch Keil uVision 5.
Open the project file located in the R2-ARC repository
cd r2-arc/TM4C_Firmware

3. Compile the Project:

In Keil uVision 5, compile the project to ensure there are no errors.
4. Upload the Firmware:

Connect your TM4C microcontroller to your computer.
Use Keil uVision 5 to upload the compiled firmware to the TM4C microcontroller.


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

