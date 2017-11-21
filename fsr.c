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
  2,    // #1
  6,    // #2
  0,    // #3
  18,   // #4
  24,   // #5
  20,   // #6
  27,   // #7
  34,   // #8
  16,   // #9
  14,   // #10
  12,   // #11
  9,    // #12
  32,   // #13
  26,   // #14
  30,   // #15
  33,   // #16
  23,   // #17
  17,   // #18
  3,    // #19
  1,    // #20
  7,    // #21
  10,   // #22
  15,   // #23
  21,   // #24
  22,   // #25
  28,   // #26
  35,   // #27
  4,    // #28
  13,   // #29
  8,    // #30
  19,   // #31
  31,   // #32
  25,   // #33
  5,    // #34
  11,   // #35
  29,   // #36
};
// initializes the global struct 'fsr'
void fsr_init(fsr_field_t *fsr)
{
    uint8_t i = 0;
    uint8_t state = 0;
    uint8_t channel = 0;

    for( i = 0; i <= (NUMBER_OF_SENSORS - 1); i++)
    {
        fsr[i].number       = fsr_map[i];     // Map physical location to the buffer
        fsr[i].state        = state;          // range: 0-(NUMBER_OF_STATES - 1)
        fsr[i].adc_channel  = channel;        // range: 0-(NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS -1)
        memset(fsr[i].value, 0x0, sizeof(fsr[i].value));
               
        channel++;
        if(channel >= NUMBER_OF_DIFFERENTIAL_ADC_CHANNELS)
        {
            channel = 0;
            state++;                            // increment the state once the .adc_channel information has been set.
        }
    }
}

/* This function copies the sensor samples from the adc_buffer into it's respective place in  fsr_field_t buffer. Each state of the multiplexer contains one sample from each of the three ADC channels*/
bool fsr_update(adc_struct_t *adc_buffer, fsr_field_t *fsr)
{
    static uint16_t sample = 0;

    if(sample < NUMBER_OF_SAMPLES)
    {
        for(uint8_t i = 0; i < NUMBER_OF_SENSORS; i++)
        {
            // The fsr[i].adc_channels can be either 0, 1, or 2, depending on the multiplexing state
            switch (fsr[i].adc_channel)
            {
                case 0: fsr[i].value[sample] = adc_buffer[fsr[i].state].adc_channel1;
                break;

                case 1: fsr[i].value[sample] = adc_buffer[fsr[i].state].adc_channel2;
                break;

                case 2: fsr[i].value[sample] = adc_buffer[fsr[i].state].adc_channel3;
                break;
            }
        }
    }
    else
    {
        //TODO Reached NUMBER_OF_SAMPLES!
        sample = 0;
        return true;
    }   
    sample++;
    return false;
}
