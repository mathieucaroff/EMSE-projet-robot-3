// OX
volatile uint8_t run_demo_move = 0;

uint8_t move_walk_start = 0;
uint8_t move_walk_done = 0;

uint16_t move_walk_shift_distance = 60;
uint16_t move_walk_forward_distance = 45;

typedef struct dr_t dr_t;
struct dr_t {
	uint16_t drive;
	uint16_t rotate;
};

/* Dealing with each robot characteristics */
typedef struct move_dr_t move_dr_t;
struct move_dr_t {
	const dr_t B0, BA, D0, O7, SB, S8;
};

const move_dr_t MOVE_DR_ALL = {
	.S8 = { .drive = 15, .rotate = 20 },
};

/* Selecting the current robot */
// const lmr_t SERVO_LMR = { 2700, 1880, 760 };
#define MOVE_DR MOVE_DR_ALL.S8


volatile uint16_t __move_count_A = 0;

void move_update(uint16_t VitDG) {
//	uint8_t b = (__move_count_A > VitDG);
//	__move_count_A = b * (__move_count_A - VitDG);
	if (VitDG >> 14) {
		while (1);
	}
	if (__move_count_A > VitDG) {
		__move_count_A -= VitDG;
	} else {
		__move_count_A = 0;
	}
}

void __move_set_direction(int16_t k, enum CMDE if_positive, enum CMDE if_negative) {
	Etat = ARRET;
	New_CMDE = 1;
	if (k >= 0) {
		CMDE = if_positive;
	} else {
		CMDE = if_negative;
	}
}

void move_require_rotate(int16_t k) {
	if (k > +360) while(1);
	if (k < -360) while(1);
	if (k == 0) return;
	__move_count_A = abs(k) * MOVE_DR.rotate / 4;
	__move_set_direction(k, DROITE, GAUCHE);
}

void move_require_drive(int16_t k) {
	__move_count_A = abs(k) * MOVE_DR.drive;
	__move_set_direction(k, AVANT, ARRIERE);
}

uint8_t inline move_moving() {
	return __move_count_A > 0;
}

void demo_move_do(uint8_t x) {
	switch (x) {
	case 0:
		move_require_drive(+60);
		break;
	case 1:
		move_require_drive(-60);
		break;
	case 2:
		move_require_rotate(+90);
		break;
	case 3:
		move_require_rotate(-90);
		break;
	default:
		break;
	}
}

void demo_move() {
	static uint8_t x = 0;

	if (move_moving()) {
		return;
	} else {
		if (x == 4) {
			CMDE = STOP;
			New_CMDE = 1;
			return;
		}
		demo_move_do(x);
		x++;
		x %= 5;
	}
}

void move_walk_do(uint8_t w) {
	switch (w) {
	case 0:
		move_require_drive(+30);
		break;
	case 1:
        // if (abs(move_walk_shift_distance) <= 1) {
        //     // pass
        // } else if (move_walk_shift_distance >= 0) {
        //     move_require_rotate(+90);
        // } else {
        //     move_require_rotate(-90);
        // }
        move_require_rotate(+90);
		break;
	case 2:
		// move_require_drive(abs(move_walk_shift_distance));
		move_require_drive(move_walk_shift_distance);
		break;
	case 3:
        // if (abs(move_walk_shift_distance) <= 1) {
        //     // pass
        // } else if (move_walk_shift_distance >= 0) {
        //     move_require_rotate(+90);
        // } else {
        //     move_require_rotate(-90);
        // }
        move_require_rotate(-90);
		break;
    case 4:
        move_require_drive(move_walk_forward_distance);
	default:
		break;
	}
}

void move_walk() {
	static uint8_t w = 0;

	if (move_moving()) {
		return;
	} else if (w < 5) {
		move_walk_do(w);
		w++;
	} else if (w < 6) {
		CMDE = STOP;
		New_CMDE = 1;
		move_walk_done = 1;
		move_walk_start = 0;
		w = 0;
	}
}

void gestion_move(void) {
	if (move_walk_start) {
		move_walk();
	} else if (run_demo_move) {
		demo_move();
	}
	return;
}
