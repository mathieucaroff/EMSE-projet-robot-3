// OX
volatile uint8_t run_demo_servo = 0;

uint8_t servo_spin_start = 0;
uint8_t servo_spin_done = 0;


typedef struct lmr_t lmr_t;
struct lmr_t {
	uint16_t left;
	uint16_t mid;
	uint16_t right;
};

/* Dealing with each robot characteristics */
typedef struct servo_lmr_t servo_lmr_t;
struct servo_lmr_t {
	const lmr_t B0, BA, D0, O7, SB, S8;
};

const servo_lmr_t SERVO_LMR_ALL = {
	.BA = { 3200, 1800, 500 },
	.S8 = { 3000, 1700, 650 },
	.B0 = { 3200, 1800, 500 },
	.O7 = { 3200, 1700, 530 },
	.SB = { 2700, 1880, 760 },
};

/* Selecting the current robot */
// const lmr_t SERVO_LMR = { 2700, 1880, 760 };
#define SERVO_LMR SERVO_LMR_ALL.S8


/**
 * @brief  Set the servo-motor to point in the given direction
 *
 * @param angle: Number, between ~600 and ~3300
 */
void set_servo_direct_sonar(int16_t angle) {
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, angle);
}

void set_servo_right(void) { set_servo_direct_sonar(SERVO_LMR.right); }
void set_servo_mid  (void) { set_servo_direct_sonar(SERVO_LMR.mid);   }
void set_servo_left (void) { set_servo_direct_sonar(SERVO_LMR.left);  }

void test_servo_forever(void) {
	uint32_t k = 0;
	set_servo_mid();

	while (1) {
		switch (k / (1000 * 1000)) {
		case 0:
		case 1:
			set_servo_right();
			break;
		case 2:
		case 5:
			set_servo_mid();
			break;
		case 3:
		case 4:
			set_servo_left();
			break;
		default:
			k = 0;
			break;
		}
		k++;
	}
}

void test_servo_sonar_forever(void) {

	uint16_t v = SERVO_LMR.right;
	uint32_t k;

	uint16_t direction = 1;

	while (1) {
		k = 64000000 / 100;
		while (--k);
		set_servo_direct_sonar(v);
		v += direction * 20;
		if (v > SERVO_LMR.left) {
			direction = -1;
		} else if (v < SERVO_LMR.right) {
			direction = +1;
		}
	}
}

void demo_servo(void) {
	static uint8_t etat;

	if(time_waiting()) {
		return;
	}
	switch (etat) {
	case 0:
		set_servo_right();
		break;
	case 1:
	case 3:
		set_servo_mid();
		break;
	case 2:
		set_servo_left();
		break;
	}
	time_require_wait_ms(4000 / (1 + etat % 2));
	etat++;
	etat %= 4;
}

void servo_spin_do(uint8_t u) {
	switch (u) {
	case 0:
		set_servo_mid();
		break;
	case 1:
		set_servo_left();
		break;
	case 2:
		set_servo_right();
		break;
	case 3:
		set_servo_mid();
		break;
	default:
		break;
	}

}

void servo_spin() {
	static uint8_t w = 0;

	if (time_waiting()) {
		return;
	} else if (w < 5) {
		servo_spin_do(w);
		time_require_wait_ms(1250);
		w++;
	} else if (w < 6) {
		servo_spin_done = 1;
		servo_spin_start = 0;
		w = 0;
	}
}

void init_servo(void) {
	set_servo_mid();
}

void gestion_servo(void) {
	if (servo_spin_start) {
		servo_spin();
	} else if (run_demo_servo) {
		demo_servo();
	}
	return;
}
