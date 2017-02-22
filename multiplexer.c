#include "stdio.h"
#include <stdbool.h>
#include <stdint.h>
#include "nrf_gpio.h"

const mux_t mux_state[12] = {state1, state2, state3, state4, state5, state6, state7, state8, state9, state10, state11, state12};

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


void mux_state_change(uint8_t i)
{
    (mux_state[i].MUX1          == ON)? nrf_gpio_clear(ENABLE1_PIN) : nrf_gpio_set(ENABLE1_PIN);
    (mux_state[i].MUX2          == ON)? nrf_gpio_clear(ENABLE2_PIN) : nrf_gpio_set(ENABLE2_PIN);
    (mux_state[i].MUX3          == ON)? nrf_gpio_clear(ENABLE3_PIN) : nrf_gpio_set(ENABLE3_PIN);
    (mux_state[i].MUX_SWITCHES  == ON)? nrf_gpio_clear(MUX_SWITCH_PIN) : nrf_gpio_set(MUX_SWITCH_PIN);
    (mux_state[i].MUX4_SWITCH   == ON)? nrf_gpio_clear(MUX4_SWITCH_PIN) : nrf_gpio_set(MUX4_SWITCH_PIN);
}
