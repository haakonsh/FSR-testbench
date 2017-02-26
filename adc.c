#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#define ADC
#include "adc.h"
#include "fsr.h"


nrf_saadc_value_t adc_buffer[NUMBER_OF_STATES][SIZE_OF_STATE_GROUPS];
nrf_saadc_value_t *adc_buffer_p = &adc_buffer[0][0];

void adc_init(void)
{
    nrf_drv_saadc_init(&adc_config, adc_evt_handler);

    nrf_saadc_buffer_init(adc_buffer_p, ADC_BUFFER_SIZE);

    APP_ERROR_CHECK(nrf_drv_saadc_calibrate_offset());

    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL1, &adc_channel1_cfg));
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL2, &adc_channel2_cfg));
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL3, &adc_channel3_cfg));
}

void adc_sample_state(uint8_t state)
{
  APP_ERROR_CHECK(nrf_drv_saadc_buffer_convert(&adc_buffer[state][0], SIZE_OF_STATE_GROUPS));
  APP_ERROR_CHECK(nrf_drv_saadc_sample());
}
