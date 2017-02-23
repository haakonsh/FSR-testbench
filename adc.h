#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_saadc.h"
#include "psr.h"
#include "main.h"

nrf_drv_saadc_config_t adc_config =
{
    .resolution         = NRF_SAADC_RESOLUTION_8BIT,
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

typedef struct
{
  nrf_saadc_value_t buffer[SIZE_OF_STATE_GROUPS];
}adc_buffer_t;

void adc_init(void);
void adc_sample(uint8_t state);
extern adc_buffer_t adc_buffer[NUMBER_OF_STATES];
