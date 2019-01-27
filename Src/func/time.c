void time_require_wait_ms(int16_t k) {
	if (k < 0) while(1);
	if (k > 10000) while(1);
	if (k == 0) return;

	__time_tick_count_A = ((int32_t) k) * T_200_MS / 200;
}


void time_sleep(int16_t k) {
	time_require_wait_ms(k);

	while (time_waiting());
}

void test_time_forever() {

	void inline s(int16_t k) { time_sleep(k); }

	while (1) {
		set_servo_right();s(9999);

		set_servo_mid();  s(2000);
		set_servo_left(); s(2000);
		set_servo_mid();  s(2000);
		set_servo_left(); s(2000);

		set_servo_mid();  s(4000);
		set_servo_left(); s(4000);
		set_servo_mid();  s(4000);
		set_servo_left(); s(4000);

		set_servo_mid();  s(8000);
		set_servo_left(); s(8000);
		set_servo_mid();  s(8000);
		set_servo_left(); s(8000);
	}
}
