#include <iostream>
#include <cstring>
#include "wiringPiSPI.h"
#include "wiringPi.h" 

int main() {
    int spiChannel = 0;             // SPI channel (0 or 1 for Raspberry Pi)
    int speed = 5000000;            // SPI speed set to 5 MHz
    unsigned char data[] = {'F'};   // Data buffer for SPI communication

    //unsigned char data[] = {'F', 'B', 'L', 'R', 'P', 'Q', 'S'}    //for future use
    /*'F' = Forward, 'B'= backwards, 'L' = left turn, 'R' = right turn, 
    'P' = Right Pivot, 'Q' = Left Pivot, 'S' = Stop*/
    
    // Initialize the SPI channel
    if (wiringPiSPISetup(spiChannel, speed) == -1) {
        std::cerr << "Failed to setup SPI communication.\n";
        return 1;
    }

    // SPI communication. Send and receive data. Print error message if SPI Fails
    if (wiringPiSPIDataRW(spiChannel, data, sizeof(data)) == -1) {
        std::cerr << "Failed to send data over SPI.\n";
        return 1;
    }

    // Output received data
    std::cout << "Received data: ";
    for(size_t i = 0; i < sizeof(data); ++i) {
        std::cout << "0x" << std::hex << static_cast<int>(data[i]) << " ";
    }
    std::cout << std::endl;

    // clear the buffer in order to reuse
    memset(data, 0, sizeof(data)); // Clear the buffer completely

    return 0;
}
