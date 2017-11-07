#ifndef FSR_H
#define FSR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_saadc.h"
#include "nrf_drv_saadc.h"
#include "adc.h"

#define NUMBER_OF_SENSORS                       36
#define NUMBER_OF_STATES                        12   // A state contains NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS amount of sensors
#define NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS     3   // NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS * NUMBER_OF_STATES >= NUMBER_OF_SENSORS must be true for all NUMBER_OF_SENSORS.

#define NUMBER_OF_SAMPLES                       512

// A structure containing the data of an FSR sensor
typedef struct FSR_field
{
  uint8_t number;       // Number on the physical board.
  uint8_t state;        // Which of the states the sensor belongs to
  uint8_t adc_channel;  // Which number in the state: 0,1,...,n where n = # of adc channels
  nrf_saadc_value_t value[NUMBER_OF_SAMPLES]; // The value of the sensor  
} fsr_field_t;

// Initializes the sensor data structures.
void fsr_init(fsr_field_t *fsr);

// Copies the values of the ADC samples into their respective fsr.value field.
// Returns true if all samples have been collected
bool fsr_update(adc_struct_t *adc_buffer, fsr_field_t *fsr);

#endif

