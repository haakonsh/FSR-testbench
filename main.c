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
#include "SEGGER_RTT.h"

/*********** Instantiations ******************************************************************/

extern struct fsr_field_t fsr[NUMBER_OF_SENSORS];

nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(1);

// This buffer will be filled with the raw samples from the SAADC. 
adc_struct_t adc_buffer[NUMBER_OF_STATES];

/*This is the main data array. It contains the FSR number identifier, which state it belongs to, which adc channel it belongs to, and the last adc sample. In the future the adc sample will not be stored in this array. */
struct fsr_field_t fsr_buffer[NUMBER_OF_SENSORS];

// Flag that eneables the main context to execute the next iteration of the state machine. 
// Set to true to start off the state machine.
bool adc_done_flag = true;

/************** Configs **********************************************************************/

/************** Inits ************************************************************************/

/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}
/************** Handlers *********************************************************************/

void rtc_handler(nrf_drv_rtc_int_type_t int_type)
{

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
            adc_done_flag = true;
            break;
        default:
        break;
    }
}

void print_buffer(struct fsr_field_t *m_buffer)
{
    //PRINT
    for(uint8_t i = 0; i < NUMBER_OF_SENSORS; i++)
    {
        SEGGER_RTT_printf(0,"Sensor: %2d Value: 0x%.4d \n", m_buffer[i].number, m_buffer[i].value);    
    }
    SEGGER_RTT_printf(0,"***************************\n");
    //SEGGER_RTT_printf(0,"Sensor: %2d Value: 0x%.4d \n", m_buffer[6].number, m_buffer[6].value);
}

void state_machine(void)
{
    static uint8_t state_counter = 0;

    mux_state_change(state_counter);
    adc_sample_state(state_counter, adc_buffer);
    state_counter++;
    if(state_counter >= NUMBER_OF_STATES)
    {
      state_counter = 0;
      fsr_update(adc_buffer, fsr_buffer);

      print_buffer(fsr_buffer); // pipe data to user
    
    }
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    log_init();
    fsr_init(fsr_buffer);
    multiplexer_init();
    adc_init(adc_evt_handler, adc_buffer);

    while (true)
    {
        if(adc_done_flag)
        {
            adc_done_flag = false;
            state_machine();
        } 
        __WFE();
        __SEV();
        __WFE();       
    }
}
/** @} */
