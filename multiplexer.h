//#ifndef MULTIPLEXER_H
//#define MULTIPLEXER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define ENABLE1_PIN         0       // MUX1 pin
#define ENABLE2_PIN         1       // MUX2 pin
#define ENABLE3_PIN         21      // MUX3 pin
#define MUX_SWITCH_PIN      5       // pin that triggers the switches
#define MUX4_SWITCH_PIN     6       // pin that triggers the switch on MUX4

typedef enum
{
    ON  = 0,
    OFF = 1
} mux_state_t;

typedef struct{
    mux_state_t MUX1;
    mux_state_t MUX2;
    mux_state_t MUX3;
    mux_state_t MUX_SWITCHES;
    mux_state_t MUX4_SWITCH;
}mux_t;

#ifdef MULTIPLEXER //Header guard against multiple definitions of the multiplexer states. Only the file containing #define MULTIPLEXER gets access to the following definitions.

// The various mux_t states below defines the state of the multiplexers on the PCB, in order to be able to sample each sensor.
mux_t state1 = {
    .MUX1           = ON,
    .MUX2           = OFF,
    .MUX3           = OFF,
    .MUX_SWITCHES   = OFF,
    .MUX4_SWITCH    = OFF
};
mux_t state2 = {
    .MUX1           = OFF,
    .MUX2           = ON,
    .MUX3           = OFF,
    .MUX_SWITCHES   = OFF,
    .MUX4_SWITCH    = OFF
};
mux_t state3 = {
    .MUX1           = OFF,
    .MUX2           = OFF,
    .MUX3           = ON,
    .MUX_SWITCHES   = OFF,
    .MUX4_SWITCH    = OFF
};
mux_t state4 = {
    .MUX1           = ON,
    .MUX2           = OFF,
    .MUX3           = OFF,
    .MUX_SWITCHES   = ON,
    .MUX4_SWITCH    = OFF
};
mux_t state5 = {
    .MUX1           = OFF,
    .MUX2           = ON,
    .MUX3           = OFF,
    .MUX_SWITCHES   = ON,
    .MUX4_SWITCH    = OFF
};
mux_t state6 = {
    .MUX1           = OFF,
    .MUX2           = OFF,
    .MUX3           = ON,
    .MUX_SWITCHES   = ON,
    .MUX4_SWITCH    = OFF
};
mux_t state7 = {
    .MUX1           = ON,
    .MUX2           = OFF,
    .MUX3           = OFF,
    .MUX_SWITCHES   = OFF,
    .MUX4_SWITCH    = ON
};
mux_t state8 = {
    .MUX1           = OFF,
    .MUX2           = ON,
    .MUX3           = OFF,
    .MUX_SWITCHES   = OFF,
    .MUX4_SWITCH    = ON
};
mux_t state9 = {
    .MUX1           = OFF,
    .MUX2           = OFF,
    .MUX3           = ON,
    .MUX_SWITCHES   = OFF,
    .MUX4_SWITCH    = ON
};
mux_t state10 = {
    .MUX1           = ON,
    .MUX2           = OFF,
    .MUX3           = OFF,
    .MUX_SWITCHES   = ON,
    .MUX4_SWITCH    = ON
};
mux_t state11 = {
    .MUX1           = OFF,
    .MUX2           = ON,
    .MUX3           = OFF,
    .MUX_SWITCHES   = ON,
    .MUX4_SWITCH    = ON
};
mux_t state12 = {
    .MUX1           = OFF,
    .MUX2           = OFF,
    .MUX3           = ON,
    .MUX_SWITCHES   = ON,
    .MUX4_SWITCH    = ON
};
#endif

void multiplexer_init(void);
void mux_state_change(uint8_t state_counter);

//#endif
