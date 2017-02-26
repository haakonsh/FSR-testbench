#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "adc.h"
#include "fsr.h"

extern nrf_saadc_value_t adc_buffer[NUMBER_OF_STATES][SIZE_OF_STATE_GROUPS];

struct fsr_field_t fsr[NUMBER_OF_SENSORS];

// Map of the sensors on the PCB prototype.
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

void fsr_init(void)
{
    uint8_t i,j,k = 0;

    for( i = 0; i <= (NUMBER_OF_SENSORS - 1); i++)
    {
        fsr[i].value = 0;
        fsr[i].number = fsr_map[i];
        fsr[i].state_group      = j;
        fsr[i].number_in_group  = k;
        k++;
        if(k >= SIZE_OF_STATE_GROUPS)
        {
            k = 0;
            j++;
        }
    }
}
void fsr_update(void)
{
  for(uint8_t i = 0; i <= (NUMBER_OF_SENSORS - 1); i++)
  {
    fsr[i].value = adc_buffer[fsr[i].state_group][fsr[i].number_in_group];
  }
}
