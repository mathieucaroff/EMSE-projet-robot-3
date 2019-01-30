
// OX
uint8_t low_battery = 0;

/**
 * OX pasted
 * @brief  Analog watchdog callback in non blocking mode.
 * @param  hadc: ADC handle
 * @retval None
 */
// __weak
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc) {
	low_battery = 1;
}

void check_low_battery() {
	if (low_battery) {
		HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_SET);
	}
}
