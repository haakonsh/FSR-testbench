#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_gpio.h"

#define MULTIPLEXER         //Header guard against multiple definitions of the multiplexer states.
#include "multiplexer.h"

// This array contains the information for the state of the muliplexers control signals(ON/OFF), given a 'state'. Initialized as OFF(high output).
mux_t mux_state[12] = {OFF};

// The 4 TS3A27518EPWR multilexers requires 5 control signals and 12 states in order to multiplex 36 sensors with the current circuit schematics.
void multiplexer_init(void)
{    
    mux_state[0]    = state1;
    mux_state[1]    = state2;
    mux_state[2]    = state3;
    mux_state[3]    = state4;
    mux_state[4]    = state5;
    mux_state[5]    = state6;
    mux_state[6]    = state7;
    mux_state[7]    = state8;
    mux_state[8]    = state9;
    mux_state[9]    = state10;
    mux_state[10]   = state11;
    mux_state[11]   = state12;
          
    nrf_gpio_cfg_output(ENABLE1_PIN);
    nrf_gpio_cfg_output(ENABLE2_PIN);
    nrf_gpio_cfg_output(ENABLE3_PIN);
    nrf_gpio_cfg_output(MUX4_PIN);
    nrf_gpio_cfg_output(MUX_SWITCH_PIN);

    /* The multiplexer's control signal are active low. The ENABLE1_PIN, ENABLE3_PIN, and ENABLE3_PIN are set high in order
    to disable the multiplexer circuit*/
    nrf_gpio_pin_set(ENABLE1_PIN);
    nrf_gpio_pin_set(ENABLE2_PIN);
    nrf_gpio_pin_set(ENABLE3_PIN);
    nrf_gpio_pin_set(MUX4_PIN);
    nrf_gpio_pin_set(MUX_SWITCH_PIN);
}

// This function sets the multiplexer control signal based on the given state.
void mux_state_change(uint8_t state)
{
    (mux_state[state].MUX1          == ON)? nrf_gpio_pin_clear(ENABLE1_PIN) : nrf_gpio_pin_set(ENABLE1_PIN);

    (mux_state[state].MUX2          == ON)? nrf_gpio_pin_clear(ENABLE2_PIN) : nrf_gpio_pin_set(ENABLE2_PIN);

    (mux_state[state].MUX3          == ON)? nrf_gpio_pin_clear(ENABLE3_PIN) : nrf_gpio_pin_set(ENABLE3_PIN);

    (mux_state[state].MUX4          == ON)? nrf_gpio_pin_clear(MUX4_PIN) : nrf_gpio_pin_set(MUX4_PIN);

    (mux_state[state].MUX_SWITCHES  == ON)? nrf_gpio_pin_clear(MUX_SWITCH_PIN) : nrf_gpio_pin_set(MUX_SWITCH_PIN);
}
