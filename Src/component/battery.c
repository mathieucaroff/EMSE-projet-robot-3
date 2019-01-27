
/**
 * OX pasted
 * @brief  Analog watchdog callback in non blocking mode.
 * @param  hadc: ADC handle
 * @retval None
 */
// __weak
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc) {
	HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_SET);
}
