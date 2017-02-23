#define NUMBER_OF_SENSORS     36
#define NUMBER_OF_STATES      12
#define SIZE_OF_STATE_GROUPS  3

//TODO fyll ut kartet, bytt ut 'xx' med PSR-nummeret
uint8_t psr_map[NUMBER_OF_SENSORS] =
{
  xx,  // #1
  xx,  // #2
  xx,  // #3
  xx,  // #4
  xx,  // #5
  xx,  // #6
  xx,  // #7
  xx,  // #8
  xx,  // #9
  xx,  // #10
  xx,  // #11
  xx,  // #12
  xx,  // #13
  xx,  // #14
  xx,  // #15
  xx,  // #16
  xx,  // #17
  xx,  // #18
  xx,  // #19
  xx,  // #20
  xx,  // #21
  xx,  // #22
  xx,  // #23
  xx,  // #24
  xx,  // #25
  xx,  // #26
  xx,  // #27
  xx,  // #28
  xx,  // #29
  xx,  // #30
  xx,  // #31
  xx,  // #32
  xx,  // #33
  xx,  // #34
  xx,  // #35
  xx,  // #36
}

typedef struct
{
  uint8_t number;
  uint8_t state_group;
  uint8_t number_in_group;
  uint8_t value;
}psr_field_t;

typedef struct
{
  uint16_t buffer[SIZE_OF_STATE_GROUPS];
}adc_buffer_t;

psr_field_t psr[NUMBER_OF_SENSORS];
adc_buffer_t adc_buffer[NUMBER_OF_STATES];

void adc_sample(uint8_t state)
{
  APP_ERROR_CHECK(nrf_drv_saadc_buffer_convert(&adc_buffer[state].buffer[0], SIZE_OF_STATE_GROUPS));
  APP_ERROR_CHECK(nrf_drv_saadc_sample());
}

void psr_update(void)
{
  for(i = 0; i <= (NUMBER_OF_SENSORS - 1); i++)
  {
    psr[i].value = adc_buffer[psr[i].state_group].buffer[psr[i].number_in_group];
  }
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
  }
}
