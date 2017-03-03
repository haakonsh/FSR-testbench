#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#define ADC
#include "adc.h"
#include "fsr.h"
#include "nrf_delay.h"


// This buffer will be filled with the raw samples from the SAADC. 
adc_struct_t adc_buffer[NUMBER_OF_STATES];

// nrf_saadc_value_t adc_buffer[NUMBER_OF_STATES][NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS];
// nrf_saadc_value_t *adc_buffer_p = &adc_buffer[0][0];

void adc_init(void)
{
    nrf_drv_saadc_init(&adc_config, adc_evt_handler);

    nrf_saadc_buffer_init((nrf_saadc_value_t*)adc_buffer, ADC_BUFFER_SIZE);

    APP_ERROR_CHECK(nrf_drv_saadc_calibrate_offset());

    // We need to wait for the calibration to complete or else nrf_drv_saadc_channel_init will return a NRF_ERROR_BUSY.
    while(!nrf_saadc_event_check(NRF_SAADC_EVENT_CALIBRATEDONE))
    {
        __WFE();
    }
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL1, &adc_channel1_cfg));
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL2, &adc_channel2_cfg));
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL3, &adc_channel3_cfg));
}
// This function sets the adc buffer pointer to the adress of the given state's adc_buffer. The adc_buffer has to be typcasted
// in order to point to a member of it's __packed struct type.
void adc_sample_state(uint8_t state)
{
  nrf_saadc_value_t *adc_buffer_p = (nrf_saadc_value_t *)&adc_buffer[state].adc_channel1;
  APP_ERROR_CHECK(nrf_drv_saadc_buffer_convert(adc_buffer_p, NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS));
  APP_ERROR_CHECK(nrf_drv_saadc_sample());
}
