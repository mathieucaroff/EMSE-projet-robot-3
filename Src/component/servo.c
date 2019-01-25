// OX

/**
 * @brief  Set the servo-motor to point in the given direction
 *
 * @param angle: Number, between ~600 and ~3300
 */
void set_servo_direct_sonar(int16_t angle) {
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, angle);
}

void test_servo_sonar_forever(void) {

	const lr_t servo = SERVO_LR.
	// B0;
	O7;

	uint16_t v = servo.right;
	uint32_t k;

	uint16_t direction = 1;

	while (1) {
		k = 64000000 / 100;
		while (--k)
			;
		set_servo_direct_sonar(v);
		v += direction * 20;
		if (v > servo.left) {
			direction = -1;
		} else if (v < servo.right) {
			direction = +1;
		}
	}
}

void gestion_servo(void) {
	return;
}
