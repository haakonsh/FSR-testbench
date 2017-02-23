

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

void psr_init(void);
void psr_update(void);
