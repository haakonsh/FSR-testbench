#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_saadc.h"
#include "main.h"
#include "fsr.h"

#ifdef ADC  // Header guard against defining the configs multiple times.
nrf_drv_saadc_config_t adc_config =
{
    .resolution         = NRF_SAADC_RESOLUTION_12BIT,
    .oversample         = NRF_SAADC_OVERSAMPLE_DISABLED,
    .interrupt_priority = SAADC_CONFIG_IRQ_PRIORITY,
    .low_power_mode     = SAADC_CONFIG_LP_MODE
};

nrf_saadc_channel_config_t adc_channel1_cfg =
{
    .resistor_p  = NRF_SAADC_RESISTOR_DISABLED,
    .resistor_n  = NRF_SAADC_RESISTOR_DISABLED,
    .gain        = NRF_SAADC_GAIN1_6,
    .reference   = NRF_SAADC_REFERENCE_INTERNAL,
    .acq_time    = NRF_SAADC_ACQTIME_40US,
    .mode        = NRF_SAADC_MODE_DIFFERENTIAL,
    .burst       = NRF_SAADC_BURST_DISABLED,
    .pin_p       = (nrf_saadc_input_t)(ADC_CHANNEL1_PIN_P),
    .pin_n       = (nrf_saadc_input_t)(ADC_CHANNEL1_PIN_N)
};
nrf_saadc_channel_config_t adc_channel2_cfg =
{
    .resistor_p  = NRF_SAADC_RESISTOR_DISABLED,
    .resistor_n  = NRF_SAADC_RESISTOR_DISABLED,
    .gain        = NRF_SAADC_GAIN1_6,
    .reference   = NRF_SAADC_REFERENCE_INTERNAL,
    .acq_time    = NRF_SAADC_ACQTIME_40US,
    .mode        = NRF_SAADC_MODE_DIFFERENTIAL,
    .burst       = NRF_SAADC_BURST_DISABLED,
    .pin_p       = (nrf_saadc_input_t)(ADC_CHANNEL2_PIN_P),
    .pin_n       = (nrf_saadc_input_t)(ADC_CHANNEL2_PIN_N)
};
nrf_saadc_channel_config_t adc_channel3_cfg =
{
    .resistor_p  = NRF_SAADC_RESISTOR_DISABLED,
    .resistor_n  = NRF_SAADC_RESISTOR_DISABLED,
    .gain        = NRF_SAADC_GAIN1_6,
    .reference   = NRF_SAADC_REFERENCE_INTERNAL,
    .acq_time    = NRF_SAADC_ACQTIME_40US,
    .mode        = NRF_SAADC_MODE_DIFFERENTIAL,
    .burst       = NRF_SAADC_BURST_DISABLED,
    .pin_p       = (nrf_saadc_input_t)(ADC_CHANNEL3_PIN_P),
    .pin_n       = (nrf_saadc_input_t)(ADC_CHANNEL3_PIN_N)
};

#endif
// This structure contains NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS(3) number of adc samples.
// To ensure that the members are aligned with the samples from the SAADC, we pack the struct.
__packed typedef struct
{
    nrf_saadc_value_t adc_channel1;
    nrf_saadc_value_t adc_channel2;
    nrf_saadc_value_t adc_channel3;
} adc_struct_t;
// Initializes the ADC
void adc_init(void);
// Samples the three differntial channels one time(one state), and stores the result in the corresponing adc_buffer[state].
void adc_sample_state(uint8_t state);

#endif
