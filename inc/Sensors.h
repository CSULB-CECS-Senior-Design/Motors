#ifndef SENSORS_H
#define SENSORS_H
#define IR10CM			  3448
#define CRASH             IR15CM  // 15 cm if there is less than this distance ahead of the robot, it will immediately stop
#define IR15CM            2233  // ADC output for 15cm:1.8v -> (1.8/3.3)*4095=2233 
#define IR20CM            1724  // ADC output for 20cm:1.39v -> (1.39/3.3)*4095=1724
#define IR30CM            1116  // ADC output for 30cm:0.9v -> (0.9/3.3)*4095=1116
#define IR40CM            918   // ADC output for 40cm:0.74v -> (0.74/3.3)*4095=918
#define IR80CM            496   // ADC output for 80cm:0.4v -> (0.4/3.3)*4095=496

#include "stdint.h"
// Initializes AIN2, AIN9, and AIN8 sampling three sensors: ahead, right, left
// 125k max sampling
// SS2 triggering event: software trigger, busy-wait sampling
// SS2 1st sample source: AIN2 (PE1)
// SS2 2nd sample source: AIN9 (PE4)
// SS2 interrupts: enabled after 3rd sample but not promoted to controller
void Sensors_Init(void);

//------------ADC_In298------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: three 12-bit result of ADC conversions
// Samples AIN8, AIN9, and AIN2
// 125k max sampling
// software trigger, busy-wait sampling
// data returned by reference
// ain2 (PE1) 0 to 4095
// ain9 (PE4) 0 to 4095
void Sensors_In(uint16_t *ain2, uint16_t *ain9);

// FIR software filter method
void ReadSensorsFIRFilter(uint16_t *ain2, uint16_t *ain9);

#endif

