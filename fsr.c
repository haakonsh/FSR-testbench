#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_saadc.h"
#include "nrf_drv_saadc.h"
#include "adc.h"
#include "fsr.h"

/* Map of the sensors on the PCB prototype. This array is used to encode the physical placement
of the individual sensors to the adc samples in the 'fsr[i]' data array. This secuence of numbers is deterined
by the physical multiplexing of the sensors on the PCB. Each sensor can only be sampled when the multiplexors are in
the state of which the sensor belongs to. See the schematics for a deeper understanding of how the multiplexing is done in-circuit.*/
uint8_t fsr_map[NUMBER_OF_SENSORS] =
{
  18,  // #1
  11,  // #2
  24,  // #3
  21,  // #4
  29,  // #5
  26,  // #6
  27,  // #7
  10,  // #8
  36,  // #9
  19,  // #10
  17,  // #11
  31,  // #12
  20,  // #13
  4,   // #14
  13,  // #15
  12,  // #16
  16,  // #17
  15,  // #18
  23,  // #19
  6,   // #20
  5,   // #21
  8,   // #22
  2,   // #23
  32,  // #24
  28,  // #25
  35,  // #26
  25,  // #27
  30,  // #28
  7,   // #29
  1,   // #30
  33,  // #31
  14,  // #32
  3,   // #33
  34,  // #34
  9 ,  // #35
  22,  // #36
};
// initializes the global struct 'fsr'
void fsr_init(struct fsr_field_t *fsr)
{
    uint8_t i,state,channel = 0;

    for( i = 0; i <= (NUMBER_OF_SENSORS - 1); i++)
    {
        fsr[i].value        = 0;                    // Set all values to 0
        fsr[i].number       = fsr_map[i];           // Map physical location to the buffer
        fsr[i].state        = state;                // range: 0-(NUMBER_OF_STATES - 1)
        fsr[i].adc_channel  = channel;              // range: 0-(NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS -1)
        channel++;
        if(channel >= NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS)
        {
            channel = 0;
            state++;                            // increment the state once the .adc_channel information has been set.
        }
    }
}

// This function copies the sensor samples from the adc_buffer into it's respective fsr_field_t struct.
void fsr_update(adc_struct_t *adc_buffer, struct fsr_field_t *fsr)
{
  for(uint8_t i = 0; i <= (NUMBER_OF_SENSORS - 1); i++)
  {
    // The fsr[i].adc_channels can be either 0, 1, or 2, depending on the multiplexing
    switch (fsr[i].adc_channel)
    {
        case 0: fsr[i].value = adc_buffer[fsr[i].state].adc_channel1;
        break;

        case 1: fsr[i].value = adc_buffer[fsr[i].state].adc_channel2;
        break;

        case 2: fsr[i].value = adc_buffer[fsr[i].state].adc_channel3;
        break;
    }
  }
}
