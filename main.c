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
#include "app_timer.h"
#include "app_util_platform.h"
#include "boards.h"
#include "bsp.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_gpiote.h"
#include "main.h"
#include "multiplexer.h"
#include "adc.h"
#include "fsr.h"

extern struct fsr_field_t fsr[NUMBER_OF_SENSORS];

extern nrf_saadc_value_t adc_buffer[NUMBER_OF_STATES][SIZE_OF_STATE_GROUPS];

nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(0);

nrf_drv_gpiote_pin_t pin1 = 16;


/************** Configs **********************************************************************/
nrf_drv_rtc_config_t rtc_cfg =
{                                                                                                \
    .prescaler          = RTC_FREQ_TO_PRESCALER(RTC_DEFAULT_CONFIG_FREQUENCY),                   \
    .interrupt_priority = RTC_DEFAULT_CONFIG_IRQ_PRIORITY,                                       \
    .reliable           = RTC_DEFAULT_CONFIG_RELIABLE,                                           \
    .tick_latency       = RTC_US_TO_TICKS(NRF_MAXIMUM_LATENCY_US, RTC_DEFAULT_CONFIG_FREQUENCY)  \
};


nrf_drv_gpiote_out_config_t pin1_cfg =
{
    .action     = NRF_GPIOTE_POLARITY_TOGGLE,
    .init_state = NRF_GPIOTE_INITIAL_VALUE_LOW,
    .task_pin   = true
};

 /************** Inits ************************************************************************/

void rtc_init(void)
{
    APP_ERROR_CHECK(nrf_drv_rtc_init(&rtc, &rtc_cfg, rtc_handler));
}

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
  if(p_event == NRF_DRV_SAADC_EVT_DONE){state_machine();}
}

void state_machine(void)
{
    static uint8_t state_counter = 0;

    state_change(state_counter);
    adc_sample(state_counter);
    state_counter++;
    if(state_counter >= 12)
    {
      state_counter = 0;
      fsr_update();
      //TODO pipe data to user
    }
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    fsr_init();
    multiplexer_init();
    adc_init();

    while (true)
    {

    }
}
/** @} */
