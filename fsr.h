#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define NUMBER_OF_SENSORS     36
#define NUMBER_OF_STATES      12
#define SIZE_OF_STATE_GROUPS  3

struct fsr_field_t
{
  uint8_t number;
  uint8_t state_group;
  uint8_t number_in_group;
  uint16_t value;   
};

void fsr_init(void);
void fsr_update(void);
