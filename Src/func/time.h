/*
 * A basic time management system.
 * It requires `time_tick` to be called from some
 * regular interruption.
 *
 * @author Mathieu CAROFF <mathieu.caroff@free.fr>
 */

volatile uint16_t __time_tick_count_A = 0;

void inline time_tick(void) {
	// if(__time_tick_count_A) --__time_tick_count_A;
	__time_tick_count_A -= !!__time_tick_count_A;
}

uint8_t inline time_waiting() {
	return __time_tick_count_A > 0;
}

void time_require_wait_ms(int16_t k);
void time_sleep(int16_t k);
void test_time_forever();
