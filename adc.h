#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_saadc.h"

#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))

#define ADC_BUFFER_SIZE     1024 //TODO Should be based on NUMBER_OF_SAMPLES in fsr.h

#define ADC_CHANNEL1        0
#define ADC_CHANNEL2        1
#define ADC_CHANNEL3        2

#define ADC_CHANNEL1_PIN_P  NRF_SAADC_INPUT_AIN4    // V1/2+ p0.28
#define ADC_CHANNEL1_PIN_N  NRF_SAADC_INPUT_AIN2    // V1/2- p0.04

#define ADC_CHANNEL2_PIN_P  NRF_SAADC_INPUT_AIN1    // V3/4+ p0.03
#define ADC_CHANNEL2_PIN_N  NRF_SAADC_INPUT_AIN5    // V3/4- p0.29

#define ADC_CHANNEL3_PIN_P  NRF_SAADC_INPUT_AIN6    // V5/6+ p0.30
#define ADC_CHANNEL3_PIN_N  NRF_SAADC_INPUT_AIN7    // V5/6- p0.31

// This structure contains NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS(3) number of adc samples.
// To ensure that the members are aligned with the samples from the SAADC, we pack the struct.
__packed typedef struct
{
    nrf_saadc_value_t adc_channel1;
    nrf_saadc_value_t adc_channel2;
    nrf_saadc_value_t adc_channel3;
    nrf_saadc_value_t padding;
}adc_struct_t;

// Initializes the ADC
void adc_init(nrf_drv_saadc_event_handler_t  event_handler, adc_struct_t *adc_buffer);
// Samples the three differntial channels one time(one state), and stores the result in the corresponing adc_buffer[state].
void adc_state_buffer_change(uint8_t state, adc_struct_t *adc_buffer_p);

void set_calibrate_flag(void);

#endif
