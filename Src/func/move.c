// OX
typedef struct dr_t dr_t;
struct dr_t {
	uint16_t drive;
	uint16_t rotate;
};

/* Dealing with each robot characteristics */
typedef struct move_dr_t move_dr_t;
struct move_dr_t {
	const dr_t B0, BA, D0, O7, SB;
};

const move_dr_t MOVE_DR_ALL = {
//	.BA = { },
//	.B0 = { },
//	.O7 = { },
	.SB = { 20, 10 },
};

/* Selecting the current robot */
// const lmr_t SERVO_LMR = { 2700, 1880, 760 };
#define MOVE_DR MOVE_DR_ALL.SB


volatile uint16_t __move_count_A = 0;

void move_update(void) {
	uint8_t b = (__move_count_A > VitD + VitG);
	__move_count_A = b * (__move_count_A - VitD - VitG);
}

void __move_set_direction(int16_t k, enum CMDE if_positive, enum CMDE if_negative) {
	Etat = ARRET;
	New_CMDE = 1;
	if (k >= 0) {
		CMDE = if_positive;
	} else {
		CMDE = if_negative;
	}
	Gestion_Commandes();
}

void move_require_rotate(int16_t k) {
	if (k > +360) while(1);
	if (k < -360) while(1);
	if (k == 0) return;
	__move_count_A = k * MOVE_DR.rotate;
	__move_set_direction(k, DROITE, GAUCHE);
}

void move_require_drive(int16_t k) {
	__move_count_A = k;
	__move_set_direction(k, AVANT, ARRIERE);
}

uint8_t inline move_moving() {
	return __move_count_A > 0;
}

void mm() {
	while (move_moving()) {
		Calcul_Vit();
		move_update();
		regulateur();
	}
}

void test_move_turn_forever() {
	while (1) {
		move_require_rotate(+45); mm();
		move_require_rotate(-45); mm();
		move_require_rotate(+45); mm();
		move_require_rotate(-45); mm();

		move_require_rotate(+90); mm();
		move_require_rotate(-90); mm();
		move_require_rotate(+90); mm();
		move_require_rotate(-90); mm();

		move_require_rotate(+180); mm();
		move_require_rotate(-180); mm();
		move_require_rotate(+180); mm();
		move_require_rotate(-180); mm();

		move_require_rotate(+360); mm();
		move_require_rotate(-360); mm();
		move_require_rotate(-360); mm();
		move_require_rotate(+360); mm();
	}
}

void test_move_drive_forever() {
	while (1) {
		move_require_drive(+20); mm();
		move_require_drive(-20); mm();
		move_require_drive(+20); mm();
		move_require_drive(-20); mm();

		move_require_drive(+40); mm();
		move_require_drive(-40); mm();
		move_require_drive(+40); mm();
		move_require_drive(-40); mm();

		move_require_drive(+80); mm();
		move_require_drive(-80); mm();
		move_require_drive(+80); mm();
		move_require_drive(-80); mm();
	}
}

void test_move_forever() {
	uint32_t k;
	while (1) {
		move_require_drive(+20);  mm();
		move_require_drive(-20);  mm();

		move_require_rotate(+45); mm();
		move_require_rotate(-45); mm();

		move_require_rotate(+90); mm();
		move_require_rotate(-90); mm();

		move_require_rotate(+90); mm();
		move_require_drive(+40);  mm();
		move_require_rotate(+90); mm();
		move_require_drive(+40);  mm();
		move_require_rotate(-90); mm();
		move_require_drive(-40);  mm();
		move_require_rotate(+90); mm();
		move_require_drive(-40);  mm();
		move_require_rotate(+180); mm();

		k = 3 * 1000 * 1000;
		while (--k);
	}
}
