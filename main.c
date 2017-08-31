/* Copyright (c) 2009 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file
* @brief Example template project.
* @defgroup nrf_templates_example Example Template
*
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nrf_gpio.h"
#include "nordic_common.h"
#include "nrf_delay.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "boards.h"
#include "bsp.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_gpiote.h"
#include "multiplexer.h"
#include "adc.h"
#include "fsr.h"
#include "main.h"

extern struct fsr_field_t fsr[NUMBER_OF_SENSORS];

nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(1);

nrf_drv_gpiote_pin_t pin1 = 16;

// This buffer will be filled with the raw samples from the SAADC. 
adc_struct_t adc_buffer[NUMBER_OF_STATES];

/*This is the main data array. It contains the FSR number identifier, which state it belongs to, which adc channel it belongs to,
and the last adc sample. In the future the adc sample will not be stored in this array. */
struct fsr_field_t fsr_buffer[NUMBER_OF_SENSORS];


/************** Configs **********************************************************************/
nrf_drv_gpiote_out_config_t pin1_cfg =
{
    .action     = NRF_GPIOTE_POLARITY_TOGGLE,
    .init_state = NRF_GPIOTE_INITIAL_VALUE_LOW,
    .task_pin   = true
};

 /************** Inits ************************************************************************/

void gpiote_init(void)
{
    APP_ERROR_CHECK(nrf_drv_gpiote_init());

    APP_ERROR_CHECK(nrf_drv_gpiote_out_init(pin1, &pin1_cfg));
}

/************** Handlers **********************************************************************/
void rtc_handler(nrf_drv_rtc_int_type_t int_type)
{

}

void adc_evt_handler(nrf_drv_saadc_evt_t const *p_event)
{
    nrf_drv_saadc_evt_type_t event = p_event->type;
    switch(event)
    {
        case NRF_DRV_SAADC_EVT_CALIBRATEDONE: 
            set_calibrate_flag();
            break;
            
        case NRF_DRV_SAADC_EVT_LIMIT: 
            break;

        case NRF_DRV_SAADC_EVT_DONE: 
            break;
        default:
        break;
    }
}

void state_machine(void)
{
    static uint8_t state_counter = 0;

    mux_state_change(state_counter);
    adc_sample_state(state_counter, adc_buffer);
    state_counter++;
    if(state_counter >= 12)
    {
      state_counter = 0;
      fsr_update(adc_buffer, fsr_buffer);

      //TODO pipe data to user
    }
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    fsr_init(fsr_buffer);
    multiplexer_init();
    adc_init(adc_evt_handler, adc_buffer);

    while (true)
    {
        state_machine();
        
    }
}
/** @} */
