void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART3) {

		New_CMDE = 1;

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

		case 'D':{
			// disconnect bluetooth
			break;
		}

		case 'W': {
			// Front Lights ON
			// HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_SET);
			move_walk_start = 1;
			break;
		}
		case 'w': {
			// Front Lights OFF
			// HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_RESET);
			move_walk_start = 0;
			break;
		}

		case 'X': {
			// Extra ON
			HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_SET);
			break;
		}
		case 'x': {
			// Extra OFF
			HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_RESET);
			break;
		}

		case 'V': {
			// Horn ON
			set_servo_left();
			CMDE = DEMO_SERVO_ON;
			New_CMDE = 1;
			break;
		}
		case 'v': {
			// Horn OFF
			CMDE = DEMO_SERVO_OFF;
			set_servo_mid();
			New_CMDE = 1;
			break;
		}

		case 'U': {
			// Back Light ON
			CMDE = DEMO_MOVE_ON;
			New_CMDE = 1;
			break;
		}
		case 'u': {
			// Back Light OFF
			CMDE = DEMO_MOVE_OFF;
			New_CMDE = 1;
			break;
		}

		default:
			New_CMDE = 1;
			break;
		}

		HAL_UART_Receive_IT(&huart3, &BLUE_RX, 1);

	}
}
