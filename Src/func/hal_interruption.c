void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART3) {

		switch (BLUE_RX) {
		case 'F': {
			CMDE = AVANT;
			//New_CMDE = 1;
			break;
		}

		case 'B': {
			CMDE = ARRIERE;
			//New_CMDE = 1;
			break;
		}

		case 'L': {
			CMDE = GAUCHE;
			//New_CMDE = 1;
			break;
		}

		case 'R': {
			CMDE = DROITE;
			//New_CMDE = 1;
			break;
		}

		case 'D': {
			// disconnect bluetooth
			break;
		}
		default:
			New_CMDE = 1;
		}

		HAL_UART_Receive_IT(&huart3, &BLUE_RX, 1);
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
//
//	Dist_ACS_3 = adc_buffer[0] - adc_buffer[4];
//	Dist_ACS_4 = adc_buffer[3] - adc_buffer[7];
//	Dist_ACS_1 = adc_buffer[1] - adc_buffer[5];
//	Dist_ACS_2 = adc_buffer[2] - adc_buffer[6];

	// [+0] [+1]
	Dist_ACS_3 = adc_buffer[0] - adc_buffer[5]; // OX
	Dist_ACS_4 = adc_buffer[3] - adc_buffer[8]; // OX
	Dist_ACS_1 = adc_buffer[1] - adc_buffer[6]; // OX
	Dist_ACS_2 = adc_buffer[2] - adc_buffer[7]; // OX
	HAL_ADC_Stop_DMA(hadc);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim) {
	static unsigned char cpt = 0;

	if (htim->Instance == TIM2) {
		cpt++;
		Time++;
		Tech++;

		time_tick();

		switch (cpt) {
		case 1: {
			HAL_GPIO_WritePin(IR3_out_GPIO_Port, IR3_out_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(IR4_out_GPIO_Port, IR4_out_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(IR1_out_GPIO_Port, IR1_out_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(IR2_out_GPIO_Port, IR2_out_Pin, GPIO_PIN_SET);
			break;
		}
		case 2: {
			// HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adc_buffer, 8);
			HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adc_buffer, 10); // OX
			break;
		}
		case 3: {
			HAL_GPIO_WritePin(IR3_out_GPIO_Port, IR3_out_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(IR4_out_GPIO_Port, IR4_out_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(IR1_out_GPIO_Port, IR1_out_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(IR2_out_GPIO_Port, IR2_out_Pin, GPIO_PIN_RESET);
			break;
		}
		case 4: {
			// HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adc_buffer, 8);
			HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adc_buffer, 10); // OX
			break;
		}
		default:
			cpt = 0;
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	static unsigned char TOGGLE = 0;

	if (TOGGLE)
		CMDE = STOP;
	else
		CMDE = START;
	TOGGLE = ~TOGGLE;
	New_CMDE = 1;

}

