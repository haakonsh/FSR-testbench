


void adc_init(void)
{

    nrf_drv_saadc_init(&adc_config, adc_evt_handler);

    nrf_saadc_buffer_init(adc_buffer, ADC_BUFFER_SIZE);

    APP_ERROR_CHECK(nrf_drv_saadc_calibrate_offset());

    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL1, &adc_channel1_cfg));
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL2, &adc_channel2_cfg));
    APP_ERROR_CHECK(nrf_drv_saadc_channel_init(ADC_CHANNEL3, &adc_channel3_cfg));

}

void adc_state_change(uint8_t i)
{
    //TODO create array of adc state structs
    (mux_state[i].MUX1          == ON)? nrf_gpio_clear(ENABLE1_PIN) : nrf_gpio_set(ENABLE1_PIN);
    (mux_state[i].MUX2          == ON)? nrf_gpio_clear(ENABLE2_PIN) : nrf_gpio_set(ENABLE2_PIN);
    (mux_state[i].MUX3          == ON)? nrf_gpio_clear(ENABLE3_PIN) : nrf_gpio_set(ENABLE3_PIN);
    (mux_state[i].MUX_SWITCHES  == ON)? nrf_gpio_clear(MUX_SWITCH_PIN) : nrf_gpio_set(MUX_SWITCH_PIN);
    (mux_state[i].MUX4_SWITCH   == ON)? nrf_gpio_clear(MUX4_SWITCH_PIN) : nrf_gpio_set(MUX4_SWITCH_PIN);
}
