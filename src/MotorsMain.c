#include "tm4c123gh6pm.h"
#include "MotorSetup.h"
#include "MotorControl.h"
#include "PLL.h"
#include "LED.h"
#include "Switches.h"
#include "SPI.h"
#include "Sensors.h"

#define LEFTPOWER	0.85*PERIOD
#define RIGHTPOWER	0.85*PERIOD

// basic functions defined at end of startup.s
extern void DisableInterrupts(void); // Disable interrupts
extern void WaitForInterrupt(void);  // low power mode
extern void EnableInterrupts(void);  // Enable interrupts

void GPIOPortF_Handler(void);
void system_init();
void steering(uint16_t ahead_dist,uint16_t behind_dist);
uint16_t receivedData;

// Finite State Machine for motor States
typedef enum {
    STATE_STOP,
    STATE_FORWARD,
    STATE_BACKWARD,
    STATE_TURN_LEFT,
    STATE_TURN_RIGHT,
    STATE_PIVOT_LEFT,
    STATE_PIVOT_RIGHT
} MotorState;

// Array of function pointers for motor control functions located in MotorControl.C
void (*stateActions[STATE_COUNT])(void) = {
    stop_motors,      // STATE_STOP
    move_forward,     // STATE_FORWARD
    move_backward,    // STATE_BACKWARD
    turn_left,        // STATE_TURN_LEFT
    turn_right,       // STATE_TURN_RIGHT
    pivot_left,       // STATE_PIVOT_LEFT
    pivot_right       // STATE_PIVOT_RIGHT
};

int main(void) {
    uint16_t ahead, behind;
    MotorState currentState = STATE_STOP; // Initial state

    DisableInterrupts();
    system_init();
    EnableInterrupts();

    // Initial sensor readings for filtering
    for (int x = 0; x < 10; x++) {
        ReadSensorsFIRFilter(&ahead, &behind); // Sensor test
    }

    while (1) {
        ReadSensorsFIRFilter(&ahead, &behind);	// Read sensor values
        uint8_t frontDistance = convert_to_centimeter(ahead);	//hold front IR Sensor Values
        uint8_t backDistance = convert_to_centimeter(behind);	//hold back IR Sensor Values
        uint16_t transmitData = encode_distance(frontDistance, backDistance);	// Encoded first byte to hold front IR Sensor Values and second byte to hold the back IR Sensor value

        SPI_receive(&receivedData);  //wait to receive motor commands from pi 5 via SPI

        // State motor logic depending on what command (unsigned char) is recieved from raspberry pi 5
        switch (receivedData) {
            case 'W':
                currentState = STATE_FORWARD;
                break;
            case 'S':
                currentState = STATE_BACKWARD;
                break;
            case 'A':
                currentState = STATE_TURN_LEFT;
                break;
            case 'D':
                currentState = STATE_TURN_RIGHT;
                break;
            case 'P':
                currentState = STATE_PIVOT_RIGHT;
                break;
            case 'O':
                currentState = STATE_PIVOT_LEFT;
                break;
            case 'Q':
                currentState = STATE_STOP;
                break;
            default:
                currentState = STATE_STOP;
                break;
        }

        // Execute the motor direction for the current state
        pwm_duty(LEFTPOWER, RIGHTPOWER);
        stateActions[currentState]();

	// Send both sensor values back
        SPI_transmit_word(transmitData);
    }
}

//System Initializations
void system_init() {
	motors_init();
	PLL_Init();
	led_init();
	SPI_slave_init();
	switch_init();
	Sensors_Init();
}

// Switch Interrupt Handler
void GPIOPortF_Handler(void) { 
	if(GPIO_PORTF_RIS_R&SW2) {	// SW2 pressed
		GPIO_PORTF_ICR_R = SW2;	// acknowledge flag
		pwm_duty(LEFTPOWER, RIGHTPOWER);
		stop_motors();			// Emergency stop
	}
	if(GPIO_PORTF_RIS_R&SW1) {	// SW1 pressed
		GPIO_PORTF_ICR_R = SW1;	// acknowledge flag
		pwm_duty(LEFTPOWER, RIGHTPOWER);
		move_forward();
	}
}
