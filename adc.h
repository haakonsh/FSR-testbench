#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_saadc.h"

#define ADC_BUFFER_SIZE     1024 


#define ADC_CHANNEL1        1
#define ADC_CHANNEL2        2
#define ADC_CHANNEL3        3

#define ADC_CHANNEL1_PIN_P  3       // V1/2+
#define ADC_CHANNEL1_PIN_N  4       // V1/2-

#define ADC_CHANNEL2_PIN_P  28      // V3/4+
#define ADC_CHANNEL2_PIN_N  29      // V3/4-

#define ADC_CHANNEL3_PIN_P  30      // V5/6+
#define ADC_CHANNEL3_PIN_N  31      // V5/6-

// This structure contains NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS(3) number of adc samples.
// To ensure that the members are aligned with the samples from the SAADC, we pack the struct.
__packed typedef struct
{
    nrf_saadc_value_t adc_channel1;
    nrf_saadc_value_t adc_channel2;
    nrf_saadc_value_t adc_channel3;
}adc_struct_t;

// Initializes the ADC
void adc_init(nrf_drv_saadc_event_handler_t  event_handler, adc_struct_t *adc_buffer);
// Samples the three differntial channels one time(one state), and stores the result in the corresponing adc_buffer[state].
void adc_sample_state(uint8_t state, adc_struct_t *adc_buffer_p);

void set_calibrate_flag(void);

#endif
