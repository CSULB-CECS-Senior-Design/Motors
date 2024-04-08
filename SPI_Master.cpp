#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <cstring>

class Movements {
private:
    bool spiChannel; // SPI Channel 0
    unsigned int speed; // 5 MHz

public:
    Movements() {
        spiChannel = 0;
        speed = 5000000;
        wiringPiSPISetup(spiChannel, speed);
    }

    Movements(bool spiChannel, unsigned int speed) {
        this->spiChannel = spiChannel;
        this->speed = speed;
        wiringPiSPISetup(spiChannel, speed);
    }

    void test_commands() {
        // Commands to be sent
        unsigned char data[] = {'W', 'A', 'S', 'D', 'O', 'P', 'Q'};    //W = foward, A = Left turn, S = backwards, D = right turn,  O = left pivot, P = right pivot, Q = Stop
        for (int i = 0; i <7; ++i) {
            unsigned char toSend [1] = {data[i]};    //buffer to send character
            std::cout << "attempting to send 0x " << std::hex << static_cast<int>(data[i]) << std::endl;    
            wiringPiSPIDataRW(spiChannel, toSend, sizeof(toSend));    // send and receive data via SPI
            std::cout << "Sent: 0x" << std::hex << static_cast<int>(data[i]) << ", ";   // sent message message
            std::cout << "Received Data: 0x" << std::hex << static_cast<int>(toSend[0]) << std::endl;    // received message
            delay(2000);    // Delay for 2000ms or 2 sec
        }
    }

    void move_forward() {
        unsigned char forward[1] = {'W'};
        wiringPiSPIDataRW(spiChannel, forward, sizeof(forward)); // Send and receive data via SPI
       // std::cout << "Received Data: 0x" << std::hex << static_cast<int>(forward[0]) << std::endl; // received message
    }

    void move_left() {
        unsigned char left[1] = {'A'};
        wiringPiSPIDataRW(spiChannel, left, sizeof(left)); // Send and receive data via SPI
       // std::cout << "Received Data: 0x" << std::hex << static_cast<int>(left[0]) << std::endl; // received message
    }

    void move_backwards() {
        unsigned char backwards[1] = {'S'};
        wiringPiSPIDataRW(spiChannel, backwards, sizeof(backwards)); // Send and receive data via SPI
     //   std::cout << "Received Data: 0x" << std::hex << static_cast<int>(backwards[0]) << std::endl; // received message
    }

    void move_right() {
        unsigned char right[1] = {'D'};
        wiringPiSPIDataRW(spiChannel, right, sizeof(right)); // Send and receive data via SPI
     //   std::cout << "Received Data: 0x" << std::hex << static_cast<int>(right[0]) << std::endl; // received message
    }

    void pivot_left() {
        unsigned char pivot_left[1] = {'O'};
        wiringPiSPIDataRW(spiChannel, pivot_left, sizeof(pivot_left)); // Send and receive data via SPI
     //   std::cout << "Received Data: 0x" << std::hex << static_cast<int>(pivot_left[0]) << std::endl; // received message
    }

    void pivot_right() {
        unsigned char pivot_right[1] = {'P'};
        wiringPiSPIDataRW(spiChannel, pivot_right, sizeof(pivot_right)); // Send and receive data via SPI
    //    std::cout << "Received Data: 0x" << std::hex << static_cast<int>(pivot_right[0]) << std::endl; // received message
    }

    void stop() {
        unsigned char stop[1] = {'Q'};
        wiringPiSPIDataRW(spiChannel, stop, sizeof(stop)); // Send and receive data via SPI
     //   std::cout << "Received Data: 0x" << std::hex << static_cast<int>(stop[0]) << std::endl; // received message
    }

    int main() {
        Movements move;
      //  move.test_commands();
        move.move_forward();
        delay(2000);    // Delay for 2 seconds or 2000ms
        move.move_left();
        delay(2000);    // Delay for 2 seconds or 2000ms
        move.move_backwards();
        delay(2000);    // Delay for 2 seconds or 2000ms
        move.move_right();
        delay(2000);    // Delay for 2 seconds or 2000ms
        move.pivot_left();
        delay(2000);    // Delay for 2 seconds or 2000ms
        move.pivot_right();
        delay(2000);    // Delay for 2 seconds or 2000ms
        move.stop();
        delay(2000);    // Delay for 2 seconds or 2000ms
        return 0;
    }
        

