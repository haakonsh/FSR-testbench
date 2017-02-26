#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_saadc.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_gpiote.h"

// #define ADC_BUFFER_SIZE     1024 //Unused

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

void gpiote_init(void);
void rtc_init(void);
// core loop, itarates through the different states of the multiplexers, samples the ADC, and stores the samples in the fsr array.
void state_machine(void);

#endif
