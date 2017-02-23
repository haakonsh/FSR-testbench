#include "psr.h"

uint8_t psr_map[NUMBER_OF_SENSORS] =
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
psr_field_t psr[NUMBER_OF_SENSORS];

}
void psr_init(void)
{
    uint8_t i,j,k = 0;

    for( i = 0; i <= (NUMBER_OF_SENSORS - 1); i++)
    {
        psr[i] = {.state_group = j, .number_in_group = k};
        k++;
        if(k >= SIZE_OF_STATE_GROUPS)
        {
            k = 0;
            j++;
        }
        psr[i].number = psr_map[i];
    }
}
void psr_update(void)
{
  for(i = 0; i <= (NUMBER_OF_SENSORS - 1); i++)
  {
    psr[i].value = adc_buffer[psr[i].state_group].buffer[psr[i].number_in_group];
  }
