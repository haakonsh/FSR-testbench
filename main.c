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
#include "app_timer.h"
#include "nrf_drv_clock.h"
#include "nrf_fstorage.h"
#include "flash.h"


#define APP_TIMER_PRESCALER 0
#define ADC_TIMER_TICKS  APP_TIMER_TICKS(20)

/*********** Instantiations ******************************************************************/

// This buffer will be filled with the raw samples from the SAADC. 
adc_struct_t adc_buffer[NUMBER_OF_STATES];

/*This is the main data array. It contains the FSR number identifier, which state it belongs to, which adc channel it belongs to, and the last adc sample. In the future the adc sample will not be stored in this array. */
fsr_field_t fsr_buffer[NUMBER_OF_SENSORS];

// Flag that eneables the main context to execute the next iteration of the state machine. 
// Set to true to start off the state machine.
bool state_machine_enter = true;

// Counter that keeps tabs on the current state of the sensor board(multiplexer), and buffers.
static uint8_t state_counter = 0;

//Flag that controls when the samples will be saved to long term storage.
bool save_data = false;

/************** Handlers *********************************************************************/

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

void adc_timer_handler(void * p_context)
{
      state_machine_enter = true;
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

            state_counter++;
            if(state_counter >= NUMBER_OF_STATES)   // All sensors have been sampled once
            {
                state_machine_enter = false;    // stop the state machine, the adc_timer handler will restart it every 20ms.
                save_data = true;               // Save the samples to their respecitive fsr buffers
                state_counter = 0;          
            }
            else
            {
                state_machine_enter = true; // iterate through the remaining states. 
            }  
            break;
        default:
        break;
    }
}

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

/**
 * @brief Function for starting the internal LFCLK XTAL oscillator.
 *
 * Note that when using a SoftDevice, LFCLK is always on.
 *
 * @return Values returned by @ref nrf_drv_clock_init.
 */
static ret_code_t clock_config(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_clock_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    nrf_drv_clock_lfclk_request(NULL);

    return NRF_SUCCESS;
}

void app_timer_initialization(void)
{
    APP_TIMER_DEF(adc_timer);
    APP_ERROR_CHECK(app_timer_init());
    APP_ERROR_CHECK(app_timer_create(&adc_timer, APP_TIMER_MODE_REPEATED, adc_timer_handler));
    APP_ERROR_CHECK(app_timer_start(adc_timer, ADC_TIMER_TICKS, NULL));
}

/************** Utils ************************************************************************/
void test_flash(void)
{
    uint32_t page_addr = START_ADDRESS; 
    uint32_t pages_to_erase = (END_ADDRESS - START_ADDRESS) >> 12; // 2^12 = 4096 the number of kB in one page, maybe related to "magic number"
    uint32_t addr_to_save = page_addr + 0;

    uint32_t data[512];
    for(uint16_t i = 0; i < 512; i++)
    {
        data[i] = i;
    }
    
    while(nrf_fstorage_is_busy(NULL)){}

    APP_ERROR_CHECK(nrf_flash_erase(page_addr, pages_to_erase, NULL));
    while(nrf_fstorage_is_busy(NULL)){}

    APP_ERROR_CHECK(nrf_flash_store(addr_to_save, &data, sizeof(data), NULL));
    while(nrf_fstorage_is_busy(NULL)){}
}
void save_fsr_to_flash(fsr_field_t *data, uint32_t len)
{
    uint32_t page_addr = START_ADDRESS; 
    uint32_t pages_to_erase = (END_ADDRESS - START_ADDRESS) >> 12; // 2^12 = 4096 the number of kB in one page
    uint32_t addr_to_save = page_addr + 0;

    while(nrf_fstorage_is_busy(NULL)){}

    APP_ERROR_CHECK(nrf_flash_erase(page_addr, pages_to_erase, NULL));
    while(nrf_fstorage_is_busy(NULL)){}

    APP_ERROR_CHECK(nrf_flash_store(addr_to_save, data, len, NULL));
    while(nrf_fstorage_is_busy(NULL)){}
}

void print_buffer(fsr_field_t *m_buffer)
{
    //PRINT
    // for(uint8_t i = 0; i < NUMBER_OF_SENSORS; i++)
    // {
    //     SEGGER_RTT_printf(0,"Sensor: %2d Value: 0x%.4d \n", m_buffer[i].number, m_buffer[i].value);    
    // }
    for(uint16_t i = 0; i <= NUMBER_OF_SAMPLES; i++)
    {
        SEGGER_RTT_printf(0,"Sensor: %2d Value: 0x%.4d \n", m_buffer[6].number, m_buffer[6].value[i]);
    } 
    SEGGER_RTT_printf(0,"***************************\n");
    //SEGGER_RTT_printf(0,"Sensor: %2d Value: 0x%.4d \n", m_buffer[6].number, m_buffer[6].value);
}

void state_machine(void)
{
    
    mux_state_change(state_counter); // change the physical state of the sensor board
    adc_state_buffer_change(state_counter, adc_buffer); // Move the SAADC buffer pointer to the next buffer         
    APP_ERROR_CHECK(nrf_drv_saadc_sample()); // Sample one state    
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{   
    APP_ERROR_CHECK(nrf_flash_init(false)); //initialise fstorage module
    test_flash();
    nrf_gpio_cfg_output(12); //TODO remove debug pin
    log_init();
    fsr_init(fsr_buffer);
    multiplexer_init();
    adc_init(adc_evt_handler, adc_buffer);
    APP_ERROR_CHECK(clock_config());
    
    
    app_timer_initialization(); 

    while (true)
    {
        if(save_data)
        {
            fsr_update(adc_buffer, fsr_buffer); // move the samples into their respective containers for long term storage
            save_data = false;
            save_fsr_to_flash(fsr_buffer, sizeof(fsr_buffer));


            // nrf_gpio_pin_set(12);   //TODO remove debug pin 
            // nrf_gpio_pin_clear(12); //TODO remove debug pin

            //print_buffer(fsr_buffer); // pipe data to user
        }
        else if(state_machine_enter)
        {
            state_machine_enter = false;
            state_machine();
        } 
        __WFE();
        __SEV();
        __WFE();       
    }
}
/** @} */
