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

int16_t adc_buffer[ADC_BUFFER_SIZE];
nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(0);


 /************** Inits ************************************************************************/

void rtc_init(void)
{
    APP_ERROR_CHECK(nrf_drv_rtc_init(&rtc, &rtc_cfg, rtc_handler));
}

void gpiote_init(void)
{
    APP_ERROR_CHECK(nrf_drv_gpiote_init());

    APP_ERROR_CHECK(nrf_drv_gpiote_out_init(pin1, pin1_cfg));
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

    mux_state_change(state_counter);
    adc_sample(state_counter);
    state_counter++;
    if(state_counter == 12)
    {
      state_counter = 0;
      psr_update();
      //TODO pipe data to user
    }
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    psr_init();
    multiplexer_init();
    adc_init();

    while (true)
    {

    }
}
/** @} */
