// Sensors.c
// Runs on TM4C123
// Provide functions that sample ADC inputs PE1, PE4, PE5
// using SS2 to be triggered by software and trigger three
// conversions,wait for them to finish, and return the three
// results.
// PE1, PE4, PE5 are connected to a sensor ahead and abckrespectively.

#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "Sensors.h"
#include "MotorSetup.h"
#include "MotorControl.h"
#include "SPI.h"

// Initializes AIN2, AIN9, and AIN8 sampling three sensors: left, center, right
// 125k max sampling
// SS2 triggering event: software trigger, busy-wait sampling
// SS2 1st sample source: AIN2 (PE1)
// SS2 2nd sample source: AIN9 (PE4)


// SS2 interrupts: enabled after 3rd sample but not promoted to controller
void Sensors_Init(void){
	volatile unsigned long delay;
	SYSCTL_RCGCADC_R |= 0x00000001; // 1) activate ADC0
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // 1) activate clock for Port E
	delay = SYSCTL_RCGCGPIO_R;      // 2) allow time for clock to stabilize
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTE_DIR_R &= ~0x12;      // 3) make PE1, PE4, and PE5 input
	GPIO_PORTE_AFSEL_R |= 0x12;     // 4) enable alternate function on PE1, PE4
	GPIO_PORTE_DEN_R &= ~0x12;      // 5) disable digital I/O on PE1, PE4, and PE5
	GPIO_PORTE_PCTL_R = GPIO_PORTE_PCTL_R&0xFFF0FF0F;
	GPIO_PORTE_AMSEL_R |= 0x12;     // 6) enable analog functionality on PE1, PE4, and PE5
	ADC0_PC_R &= ~0xF;              // 8) clear max sample rate field
	ADC0_PC_R |= 0x1;               //    configure for 125K samples/sec
	ADC0_SSPRI_R = 0x3210;          // 9) Sequencer 3 is lowest priority
	ADC0_ACTSS_R &= ~0x0004;        // 10) disable sample sequencer 2
	ADC0_EMUX_R &= ~0x0F00;         // 11) seq2 is software trigger
	ADC0_SSMUX2_R = 0x0892;         // 12) set channels for SS2
	ADC0_SSCTL2_R = 0x0600;         // 13) no D0 END0 IE0 TS0 D1 END1 IE1 TS1 D2 TS2, yes END2 IE2
	ADC0_IM_R &= ~0x0004;    	       // 14) disable SS2 interrupts
	ADC0_ACTSS_R |= 0x0004;         // 15) enable sample sequencer 2
}

//------------ADC_In298------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: three 12-bit result of ADC conversions
// Samples AIN8, AIN9, and AIN2 for left, center, right sensors
// 125k max sampling
// software trigger, busy-wait sampling
// data returned by reference
// ain2 (PE1) 0 to 4095
// ain9 (PE4) 0 to 4095

void Sensors_In(uint16_t *ain2, uint16_t *ain9){
	ADC0_PSSI_R = 0x0004;            // 1) initiate SS2
	while((ADC0_RIS_R&0x04)==0){};   // 2) wait for conversion done
	*ain2 = ADC0_SSFIFO2_R&0xFFF;    // 3A) read first result
	*ain9 = ADC0_SSFIFO2_R&0xFFF;    // 3B) read second result
	ADC0_ISC_R = 0x0004;             // 4) acknowledge completion
}

// Returns the results in the corresponding variables.  Some
// kind of filtering is required because the IR distance sensors
// output occasional erroneous spikes.  This is an FIR filter:
// y(n) = (x(n) + x(n-1))/2
// Assumes: ADC initialized by previously calling Sensors_Init()
void ReadSensorsFIRFilter(uint16_t *ain2, uint16_t *ain9){
	static uint16_t ain2previous=0; // after the first call, the value changed to 12
	static uint16_t ain9previous=0;
	uint16_t ain2newest;
	uint16_t ain9newest;
	Sensors_In(&ain2newest, &ain9newest); // sample AIN2(PE1), AIN9 (PE4)
	*ain2 = (ain2newest + ain2previous)/2;
	*ain9 = (ain9newest + ain9previous)/2;
	ain2previous = ain2newest; ain9previous = ain9newest;
}

uint16_t encodeTransmitData(uint8_t frontDistance, uint8_t backDistance) {
	return (frontDistance << 8) | backDistance;
}

void steering(uint16_t ahead_dist, uint16_t behind_dist){
	// when track is complete stop and shine blue LED 	
	if(ahead_dist > CRASH && behind_dist > CRASH ){
		stop_motors();
	}
	if (ahead_dist < IR30CM){
		pivot_right();
	}
	if (behind_dist< IR30CM){
		move_forward();
	}	
}

