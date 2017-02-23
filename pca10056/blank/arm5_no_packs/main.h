#include "stdio.h"
#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_saadc.h"
#include "nrf_drv_rtc.h"


#define ADC_BUFFER_SIZE     1024

#define ADC_CHANNEL1        1
#define ADC_CHANNEL2        2
#define ADC_CHANNEL3        3

#define ADC_CHANNEL1_PIN_P  3       // V1/2+
#define ADC_CHANNEL1_PIN_N  4       // V1/2-

#define ADC_CHANNEL2_PIN_P  28      // V3/4+
#define ADC_CHANNEL2_PIN_N  29      // V3/4-

#define ADC_CHANNEL3_PIN_P  30      // V5/6+
#define ADC_CHANNEL3_PIN_N  31      // V5/6-


void adc_evt_handler(nrf_drv_saadc_evt_t const *p_event);
void rtc_handler(nrf_drv_rtc_int_type_t int_type);

/************** Configs **********************************************************************/
nrf_drv_rtc_config_t rtc_cfg =
{                                                                                                \
    .prescaler          = RTC_FREQ_TO_PRESCALER(RTC_DEFAULT_CONFIG_FREQUENCY),                   \
    .interrupt_priority = RTC_DEFAULT_CONFIG_IRQ_PRIORITY,                                       \
    .reliable           = RTC_DEFAULT_CONFIG_RELIABLE,                                           \
.tick_latency           = RTC_US_TO_TICKS(NRF_MAXIMUM_LATENCY_US, RTC_DEFAULT_CONFIG_FREQUENCY), \
};


nrf_drv_gpiote_out_config_t pin1_cfg =
{
    .action     = NRF_GPIOTE_POLARITY_TOGGLE,
    .init_state = NRF_GPIOTE_INITIAL_VALUE_LOW,
    .task_pin   = true
};
