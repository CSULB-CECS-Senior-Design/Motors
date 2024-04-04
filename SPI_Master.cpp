#include <iostream>
#include <cstring>
#include "wiringPiSPI.h"
#include "wiringPi.h"

int main() {
    int spiChannel = 0;    // SPI Channel 0
    int speed = 5000000;    // 5 MHz
    unsigned char data[] = {'F', 'B', 'L', 'R', 'P', 'Q', 'S'};    //Commands to be sent
    size_t dataSize = sizeof(data) / sizeof(data[0]);    //Calculate the number of elements in data array
    
    //Initialize SPI Channel. Print error message if failed initialization
    if (wiringPiSPISetup(spiChannel, speed) == -1) {
        std::cerr << "Failed to setup SPI communication.\n";
        return 1;
    }

    for (size_t i = 0; i < dataSize; ++i) {
        unsigned char toSend[1] = {data[i]};    //buffer to send character
        std::cout << "Attempting to send 0x " <<std::hex << static_cast<int>(data[i]) <<std::endl;    //Debugging message attempting to send
        wiringPiSPIDataRW(spiChannel, toSend, sizeof(toSend)) ;    //Send and Receive data via SPI
    
        std::cout << "Sent: 0x" << std::hex << static_cast<int>(data[i]) << ", ";    //Character Sent during SPI communication
        std::cout << "Received data: 0x" << std::hex << static_cast<int>(toSend[0]) << std::endl;    //Character Received during SPi Communication

        delay(2000); // 2000ms or 2 sec delay
    }
    return 0;
}
