#include "cvor.h"

Cvor::Cvor(int m, bool daLiSamList) : m(m), kljucevi(nullptr), pokazivaci(nullptr), brojKljuceva(0), daLiSamList(daLiSamList) {
	if (m < 2) {
		delete this;
		std::cout << "GRESKA PRI PRAVLJENJU CVORA: m (" << m << ") JE PREMALO!" << std::endl;
		return;
	}

	kljucevi = new long long int[m - 1];
	pokazivaci = new void * [m];

	for (int i = 0; i < m; i++) {
		pokazivaci[i] = nullptr;
	}
}

/*Objekat* Cvor::pronadjiPodatak(int kljuc)
{
	if (daLiSamList) {
		for (int i = 0; i < brojKljuceva; i++) {
			if (kljuc == kljucevi[i]) {
				return pokazivaci[i];
			}
		}

		return nullptr;
	}

	for (int i = 0; i < brojKljuceva; i++) {
		if (kljuc <= kljucevi[i]) {
			return pokazivaci[i];
		}
	}

	return pokazivaci[brojKljuceva];
}*/

long long int& Cvor::operator()(const int& i) {
	/*if (i < 0 || i >= brojKljuceva) {
		return -1;
	}*/

	return kljucevi[i];
}

void*& Cvor::operator[](const int& i) {
	/*if (i < 0 || i > brojKljuceva) {
		std::cout << "GRESKA" << std::endl;
	}*/

	return pokazivaci[i];
}

/*int Cvor::ubaciKljuc(int kljuc, void*& podatak) {
	if (brojKljuceva < m - 1) {
		int i = 0;
		while (i < brojKljuceva && kljuc > kljucevi[i]) {
			i++;
		}
		
		for (int j = brojKljuceva; j > i; j--) {
			kljucevi[j] = kljucevi[j - 1];
			pokazivaci[j] = pokazivaci[j - 1];
		}

		kljucevi[i] = kljuc;
		pokazivaci[i] = podatak;

		return -1;
	}

	int vrati = 0;
	void* noviPodatak = podatak;

	int srednji = (m - 1) / 2 - 1; // MOZDA PROBLEM

	if (kljucevi[srednji] > kljuc) {
		if (m % 2 == 0) {
			vrati = kljucevi[srednji];
			podatak = pokazivaci[srednji];
		}
	}

	
}*/

Cvor* Cvor::ubaciKljuc(long long int& kljuc, void* podatak) {
	if (brojKljuceva < m - 1) {
		int i = 0;

		while (i < brojKljuceva && kljuc > kljucevi[i]) {
			i++;
		}

		for (int j = brojKljuceva; j > i; j--) {
			kljucevi[j] = kljucevi[j - 1];
		}

		int granica = 0;

		if (daLiSamList) {
			granica = brojKljuceva;
		}
		else {
			granica = brojKljuceva + 1;
		}

		for (int j = granica; j > i; j--) {
			pokazivaci[j] = pokazivaci[j - 1];
		}

		kljucevi[i] = kljuc;
		pokazivaci[i] = podatak;

		brojKljuceva++;
		return nullptr;
	} // OBICNO UBACIVANJE, NEMA PROBLEMA

	Cvor* desniBrat = new Cvor(m, daLiSamList); //STVARAMO DESNOG BRATA

	if (daLiSamList) {
		(*desniBrat)[m - 1] = pokazivaci[m - 1];
		pokazivaci[m - 1] = (void*)desniBrat;
	}	// ULANCAVAMO IH AKO SU LISTOVI

	int brojElemenataUDesnomBratu = m / 2;

	brojKljuceva++;

	int offset = brojKljuceva - brojElemenataUDesnomBratu;

	for (int i = 0; i < offset; i++) {
		if (kljuc < kljucevi[i]) {
			long long int temp1 = kljuc;
			void* temp2 = podatak;
			kljuc = kljucevi[i];
			podatak = pokazivaci[i];
			kljucevi[i] = temp1;
			pokazivaci[i] = temp2;
		}
	}

	

	for (int i = offset; i < brojKljuceva - 1; i++) {
		if (kljuc < kljucevi[i]) {
			long long int temp1 = kljuc;
			void* temp2 = podatak;
			kljuc = kljucevi[i];
			podatak = pokazivaci[i];
			(*desniBrat)(i - offset) = temp1;
			(*desniBrat)[i - offset] = temp2;
		}
		else {
			(*desniBrat)(i - offset) = kljucevi[i];
			(*desniBrat)[i - offset] = pokazivaci[i];
		}
	}

	(*desniBrat)(brojElemenataUDesnomBratu - 1) = kljuc;
	(*desniBrat)[brojElemenataUDesnomBratu - 1] = podatak;
	(*desniBrat)[brojElemenataUDesnomBratu] = pokazivaci[m - 1];

	desniBrat->brojKljuceva = brojElemenataUDesnomBratu;
	brojKljuceva = offset;

	kljuc = kljucevi[brojKljuceva - 1];
	podatak = pokazivaci[brojKljuceva - 1];

	if (!daLiSamList) {
		brojKljuceva--;
	}

	return desniBrat;
}

/*int Cvor::izbaciKljuc(long long int kljuc)
{
	if (brojKljuceva == minimalanBrojElemenata()) {
		return -1;
	}

	for (int i = 0; i < brojKljuceva; i++) {
		if (kljucevi[i] == kljuc) {
			if (daLiSamList == true) {
				delete pokazivaci[i];
			}
			
			for (int j = i; j < brojKljuceva - 1; j++) {
				kljucevi[j] = kljucevi[j + 1];
				pokazivaci[j] = pokazivaci[j + 1];
			}

			brojKljuceva--;
		}
	}

	return 0;
}*/
