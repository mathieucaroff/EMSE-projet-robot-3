void ACS(void) {
//	enum ETAT {
//		ARRET, ACTIF
		// SLEEP, ACTIF
//	};
//	static enum ETAT Etat = ARRET;

	static enum MODE Etat = SLEEP;

	static uint16_t Delta1 = 0;
	static uint16_t Delta2 = 0;
	static uint16_t Delta3 = 0;
	static uint16_t Delta4 = 0;

	switch (Etat) {
	// case ARRET: {
	case SLEEP: {
		if (Mode == ACTIF)
			Etat = ACTIF;
		else {
			CVitD = _CVitD;
			CVitG = _CVitG;
			DirD = _DirD;
			DirG = _DirG;
		}
		break;
	}
	case ACTIF: {
		if (Mode == SLEEP) {
			// Etat = ARRET;
			Etat = SLEEP;
		}
		if (_DirD == AVANCE && _DirG == AVANCE) {
			if ((Dist_ACS_1 < Seuil_Dist_1 - Delta1)
					&& (Dist_ACS_2 < Seuil_Dist_2 - Delta2)) {
				CVitD = _CVitD;
				CVitG = _CVitG;
				DirD = _DirD;
				DirG = _DirG;
				Delta1 = Delta2 = 0;
			} else if ((Dist_ACS_1 < Seuil_Dist_1)
					&& (Dist_ACS_2 > Seuil_Dist_2)) {
				CVitD = V1;
				CVitG = V1;
				DirG = AVANCE;
				DirD = RECULE;
				Delta2 = DELTA;
			} else if ((Dist_ACS_1 > Seuil_Dist_1)
					&& (Dist_ACS_2 < Seuil_Dist_2)) {
				CVitD = V1;
				CVitG = V1;
				DirD = AVANCE;
				DirG = RECULE;
				Delta1 = DELTA;
			} else if ((Dist_ACS_1 > Seuil_Dist_1)
					&& (Dist_ACS_2 > Seuil_Dist_2)) {
				CVitD = 0;
				CVitG = 0;
				DirD = RECULE;
				DirG = RECULE;
			}
		} else if (_DirD == RECULE && _DirG == RECULE) {
			if ((Dist_ACS_3 < Seuil_Dist_3 - Delta3)
					&& (Dist_ACS_4 < Seuil_Dist_4 - Delta4)) {
				CVitD = _CVitD;
				CVitG = _CVitG;
				DirD = _DirD;
				DirG = _DirG;
				Delta3 = Delta4 = 0;
			} else if ((Dist_ACS_3 > Seuil_Dist_3)
					&& (Dist_ACS_4 < Seuil_Dist_4)) {
				CVitD = V1;
				CVitG = V1;
				DirD = AVANCE;
				DirG = RECULE;
				Delta3 = DELTA;
			} else if ((Dist_ACS_3 < Seuil_Dist_3)
					&& (Dist_ACS_4 > Seuil_Dist_4)) {
				CVitD = V1;
				CVitG = V1;
				DirG = AVANCE;
				DirD = RECULE;
				Delta4 = DELTA;
			} else if ((Dist_ACS_3 > Seuil_Dist_3)
					&& (Dist_ACS_4 > Seuil_Dist_4)) {
				CVitD = 0;
				CVitG = 0;
				DirD = RECULE;
				DirG = RECULE;
			}
		} else {
			CVitD = _CVitD;
			CVitG = _CVitG;
			DirD = _DirD;
			DirG = _DirG;
		}
		break;
	}
	}
}
