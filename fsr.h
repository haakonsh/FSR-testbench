#ifndef FSR_H
#define FSR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define NUMBER_OF_SENSORS     36
#define NUMBER_OF_STATES      12    // A state(group) contains SIZE_OF_STATE_GROUPS amount of sensors
#define SIZE_OF_STATE_GROUPS  3

// A structure containing the data of an FSR sensor
struct fsr_field_t
{
  uint8_t number : 8;           // Number on the physical board.
  uint8_t state_group : 8;      // Which of the states the sensor belongs to
  uint8_t number_in_group : 8;  // Which number in the state: 0,1,...,n where n=SIZE_OF_STATE_GROUPS
  int16_t value : 16;           // The value of the sensor
};
// Initializes the sensor data structures.
void fsr_init(void);
// Copies the values of the ADC samples into their respective fsr.value field.
void fsr_update(void);

#endif
