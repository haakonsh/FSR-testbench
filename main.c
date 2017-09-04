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
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
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


/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    NRF_LOG_ERROR("Fatal");
    NRF_LOG_FINAL_FLUSH();
    //NRF_BREAKPOINT_COND;
    // On assert, the system can only recover with a reset.
#ifndef DEBUG
    NRF_LOG_INFO("Hit weak handler");
    NVIC_SystemReset();
#else
    app_error_save_and_stop(id, pc, info);
#endif // DEBUG
}

/************** Configs **********************************************************************/

 /************** Inits ************************************************************************/

/************** Handlers **********************************************************************/

void state_machine(void)
{
    static uint8_t state_counter = 0;

    mux_state_change(state_counter);
    state_counter++;
    if(state_counter >= 12)
    {
      state_counter = 0;
    }
    nrf_delay_us(10);
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    log_init();
    multiplexer_init();
    while (true)
    {
        state_machine();
    }
}
/** @} */
