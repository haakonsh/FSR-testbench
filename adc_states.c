#define NUMBER_OF_SENSORS     36
#define NUMBER_OF_STATES      12
#define SIZE_OF_STATE_GROUPS  3


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
  APP_ERROR_CHECK(nrf_drv_saadc_buffer_convert	(&adc_buffer[state].buffer[0], SIZE_OF_STATE_GROUPS));
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
  for(uint8_t i = 0; i <= (NUMBER_OF_SENSORS - 1); i++)
  {
    for(j = 0; j <= (NUMBER_OF_STATES - 1); j++)
    {
      for(k = 0; k <= (SIZE_OF_STATE_GROUPS - 1); k++)
      {
        psr[i] = {.state_group = j, .number_in_group = k};
      }
    }
  }
}
