#ifndef FSR_H
#define FSR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_saadc.h"
#include "nrf_drv_saadc.h"
#include "adc.h"

#define NUMBER_OF_SENSORS                       36
#define NUMBER_OF_STATES                        12    // A state contains NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS amount of sensors
#define NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS     3     // NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS * NUMBER_OF_STATES >= NUMBER_OF_SENSORS must be true for all NUMBER_OF_SENSORS.

// A structure containing the data of an FSR sensor
struct fsr_field_t
{
  uint8_t number            : 8;  // Number on the physical board.
  uint8_t state             : 8;  // Which of the states the sensor belongs to
  uint8_t adc_channel       : 8;  // Which number in the state: 0,1,...,n where n = # of adc channels
  nrf_saadc_value_t value   : 16; // The value of the sensor
};
// Initializes the sensor data structures.
void fsr_init(struct fsr_field_t *fsr);
// Copies the values of the ADC samples into their respective fsr.value field.
void fsr_update(adc_struct_t *adc_buffer, struct fsr_field_t *fsr);

#endif
