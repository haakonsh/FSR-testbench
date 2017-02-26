#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_gpio.h"
#define MULTIPLEXER         //Header guard against multiple definitions of the multiplexer states.
#include "multiplexer.h"
mux_t mux_state[12] = {OFF};

void multiplexer_init(void)
{
    nrf_gpio_cfg_output(ENABLE1_PIN);
    nrf_gpio_cfg_output(ENABLE2_PIN);
    nrf_gpio_cfg_output(ENABLE3_PIN);
    nrf_gpio_cfg_output(MUX_SWITCH_PIN);
    nrf_gpio_cfg_output(MUX4_SWITCH_PIN);

    nrf_gpio_pin_set(ENABLE1_PIN);
    nrf_gpio_pin_set(ENABLE2_PIN);
    nrf_gpio_pin_set(ENABLE3_PIN);
    nrf_gpio_pin_set(MUX_SWITCH_PIN);
    nrf_gpio_pin_set(MUX4_SWITCH_PIN);
}


void mux_state_change(uint8_t state)
{
    (mux_state[state].MUX1          == ON)? nrf_gpio_pin_clear(ENABLE1_PIN) : nrf_gpio_pin_set(ENABLE1_PIN);

    (mux_state[state].MUX2          == ON)? nrf_gpio_pin_clear(ENABLE2_PIN) : nrf_gpio_pin_set(ENABLE2_PIN);

    (mux_state[state].MUX3          == ON)? nrf_gpio_pin_clear(ENABLE3_PIN) : nrf_gpio_pin_set(ENABLE3_PIN);

    (mux_state[state].MUX_SWITCHES  == ON)? nrf_gpio_pin_clear(MUX_SWITCH_PIN) : nrf_gpio_pin_set(MUX_SWITCH_PIN);

    (mux_state[state].MUX4_SWITCH   == ON)? nrf_gpio_pin_clear(MUX4_SWITCH_PIN) : nrf_gpio_pin_set(MUX4_SWITCH_PIN);
}
