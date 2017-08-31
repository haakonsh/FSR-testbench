#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#define ADC
#include "adc.h"
#include "fsr.h"
#include "nrf_delay.h"

#define ADC_BUFFER_SIZE     1024 

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

bool calibrate_done_flag; 

void set_calibrate_flag(void)
{
    calibrate_done_flag = true;
}

void adc_init(nrf_drv_saadc_event_handler_t  event_handler, adc_struct_t *adc_buffer)
{
    calibrate_done_flag = false;

    nrf_drv_saadc_init(&adc_config, event_handler);

    //TODO: Don't think I need to init the adc buffer here, done automatically in nrf_drv_saadc_buff_conver.
    //nrf_saadc_buffer_init((nrf_saadc_value_t*)adc_buffer, ADC_BUFFER_SIZE);
    
    
    APP_ERROR_CHECK(nrf_drv_saadc_calibrate_offset());

    // We need to wait for the calibration to complete or else nrf_drv_saadc_channel_init will return a NRF_ERROR_BUSY.
    
    while(!calibrate_done_flag)
    {
        __WFE();
    }
    
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL1, &adc_channel1_cfg));
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL2, &adc_channel2_cfg));
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL3, &adc_channel3_cfg));
}
// This function sets the adc buffer pointer to the adress of the given state's adc_buffer. The adc_buffer has to be typcasted
// in order to point to a member of it's __packed struct type.
void adc_sample_state(uint8_t state, adc_struct_t *adc_buffer_p)
{
    // Create an array of pointers of adc_struct_t where element 0 contains the address of element 0 in our ADC buffer of adc_struct_t.
    adc_struct_t *adc_buffer[12];
    adc_buffer[0] = adc_buffer_p;
   
    APP_ERROR_CHECK(nrf_drv_saadc_buffer_convert((nrf_saadc_value_t *)adc_buffer[state]->adc_channel1, NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS));
    APP_ERROR_CHECK(nrf_drv_saadc_sample());
}
