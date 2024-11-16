#pragma once
#include"podatak.h"
#include"cvor.h"

// POTENCIJALNA GRESKA AKO NESTO NE RADI JESTE TO DA POKAZIVAC NA SLEDECI SEKVENCIJALNI CVOR NEKAD POKAZUJE NA SAMOG SEBE NMP ZASTO



using namespace std;

template <typename Element> class BPS {
private:
	Cvor* koren;
	int brojKljuceva;
	int m;

	void propagirajBrisanje(stack<Cvor*>& stek, stack<int>& indeksi);
	void popraviKraj() {
		Cvor* temp = koren;

		while (!temp->DaLiSamList()) {
			temp = (Cvor*)(*temp)[temp->brojKljuceva];
		}

		(*temp)[temp->brojKljuceva] = nullptr;
	}
public:
	//Cvor* koren;
	BPS(const BPS&) = delete;

	BPS() : BPS(3) {}

	explicit BPS(int m) : koren(nullptr), m(m), brojKljuceva(0) {
		if (m < 2) {
			delete this;
			std::cout << "GRESKA PRI PRAVLJENJU CVORA: m (" << m << ") JE PREMALO!" << std::endl;
			return;
		}
	}

	void ubaciElement(long long int kljuc, Element podatak);

	void izbrisiElement(long long int kljuc);

	void ispisi();

	Element* pronadjiElementOdredjenKljucem(long long int kljuc, int& brKoraka);

	int pronadjiElemente(long long int* kljucevi, int n) {
		int ukupanBrKoraka = 0;

		ofstream fajl("Pristupi.txt");

		bool prvi = false;

		for (int i = 0; i < n; i++) {
			int brKoraka = 0;

			if (prvi) {
				fajl << endl;
			}
			else {
				prvi = true;
			}

			Podatak* pod = pronadjiElementOdredjenKljucem(kljucevi[i], brKoraka);

			if (pod != nullptr) {
				fajl << *pod;
			}
			else {
				bool kul = true;
				if (!kul) {
					fajl << "Ne postoji podatak sa CA_ID-om " << kljucevi[i] << ".";
				}
				else {
					fajl << "NULL";
				}
			}

			ukupanBrKoraka += brKoraka;
		}

		fajl.close();
		return ukupanBrKoraka;
	}

	int pronadjiElementeSekvencijalne(long long int kljuc, int n);

	void ispisiSekvencijalno();

	int getBrojKljuceva() {
		return brojKljuceva;
	}

	~BPS();
};

template<typename Element>
int BPS<Element>::pronadjiElementeSekvencijalne(long long int kljuc, int n)
{
	int ukupanBrKoraka = 1;

	Cvor* trenutni = koren;

	while (!trenutni->DaLiSamList()) {
		ukupanBrKoraka++;
		bool nisam = true;

		for (int i = 0; i < trenutni->get_brojKljuceva(); i++) {
			if (kljuc <= (*trenutni)(i)) {
				trenutni = (Cvor*)((*trenutni)[i]);
				nisam = false;
				break;
			}
		}

		if (nisam) {
			trenutni = (Cvor*)((*trenutni)[trenutni->get_brojKljuceva()]);
		}
	}

	int indeks = -1;

	for (int i = 0; i < trenutni->get_brojKljuceva(); i++) {
		if (kljuc == (*trenutni)(i)) {
			indeks = i;
			break;
		}
	}

	if (indeks == -1) {
		cout << "Ne postoji dati kljuc." << endl;
		return ukupanBrKoraka;
	}

	ofstream fajl("SekvencijalniPristupi.txt");

	fajl << *(Element*)((*trenutni)[indeks]);

	for (int i = 1; i < n; i++) {
		if (indeks == trenutni->brojKljuceva - 1) {
			trenutni = (Cvor*)(*trenutni)[m - 1];
			indeks = 0;

			if (trenutni == nullptr) {
				fajl << endl << "Nema vise elemenata.";
				fajl.close();
				return ukupanBrKoraka;
			}
			ukupanBrKoraka++;
		}
		else {
			indeks++;
		}

		fajl << endl << *(Element*)((*trenutni)[indeks]);
	}

	fajl.close();

	return ukupanBrKoraka;
}

template <typename Element>
void BPS<Element>::ispisiSekvencijalno() {
	Cvor* tek = koren;

	if (tek == nullptr) {
		cout << "Drvo je prazno." << endl;
		return;
	}

	while (!tek->DaLiSamList()) {
		tek = (Cvor*)(*tek)[0];
	}

	while (tek != nullptr) {
		for (int i = 0; i < tek->brojKljuceva; i++) {
			cout << *(Element*)(*tek)[i] << endl;
		}

		tek = (Cvor*)(*tek)[m - 1];
	}
	cout << endl;
}

template <typename Element>
Element* BPS<Element>::pronadjiElementOdredjenKljucem(long long int kljuc, int& brKoraka) {
	Cvor* trenutni = koren;

	int brojKoraka = 1;

	while (!trenutni->DaLiSamList()) {
		brojKoraka++;
		bool nisam = true;

		for (int i = 0; i < trenutni->get_brojKljuceva(); i++) {
			if (kljuc <= (*trenutni)(i)) {
				trenutni = (Cvor*)((*trenutni)[i]);
				nisam = false;
				break;
			}
		}

		if (nisam) {
			trenutni = (Cvor*)((*trenutni)[trenutni->get_brojKljuceva()]);
		}
	}

	brKoraka = brojKoraka;

	for (int i = 0; i < trenutni->get_brojKljuceva(); i++) {
		if (kljuc == (*trenutni)(i)) {
			return (Element*)((*trenutni)[i]);
		}
	}

	return (Element*)nullptr;
}



template <typename Element>
void BPS<Element>::ispisi() { // LOS JE ISPIS
	if (brojKljuceva == 0) {
		cout << "Drvo je prazno." << endl;
		return;
	}
	
	/*queue<Cvor*> red;
	queue<Cvor*> trenutni;

	red.push(koren);

	while (!red.empty()) {
		while (!red.empty()) {
			trenutni.push(red.front());
			red.pop();
		}

		while (!trenutni.empty()) {
			Cvor* temp = trenutni.front();
			trenutni.pop();

			for (int i = 0; i < temp->get_brojKljuceva(); i++) {
				if (!temp->DaLiSamList()) {
					red.push((Cvor*)(*temp)[i]);
				}
				cout << (*temp)(i) << "|";
			}

			if (!temp->DaLiSamList()) {
				red.push((Cvor*)(*temp)[temp->get_brojKljuceva()]);
			}

			cout << "   ";
		}

		cout << endl;
	}*/

	/*struct elem {
		string prefix;
		int broj;
	};

	stack<Cvor*> stek;
	stack<int> indeksi;
	stack<elem> prefixi;
	stek.push(koren);
	prefixi.push({ "", 0 });
	indeksi.push(1);
	indeksi.push(0);


	while (!stek.empty()) {
		Cvor* trenutni = stek.top();
		elem el = prefixi.top();

		string prefix = el.prefix;
		prefixi.pop();
		prefixi.push({ prefix, el.broj + 1 });

		int indeks = indeksi.top();
		indeksi.pop();

		if (indeks == trenutni->brojKljuceva) {
			stek.pop();
			prefixi.pop();
		}
		else if (indeks == 0) {
			cout << prefix << el.broj << ":";
			for (int i = 0; i < trenutni->brojKljuceva; i++) {
				cout << " " << (*trenutni)(i);
			}
			cout << endl;
		}

		if (indeks != trenutni->brojKljuceva) {
			indeksi.push(indeks + 1);
		}
		

		if (!(trenutni->DaLiSamList())) {
			stek.push((Cvor*)(*trenutni)[indeks]);
			prefixi.push({ prefix + "    ", el.broj });
			indeksi.push(0);
		}
	}*/

	cout << "0:";

	for (int i = 0; i < koren->brojKljuceva; i++) {
		cout << " " << (*koren)(i);
	}

	cout << endl;

	struct Elem {
		Cvor* cvor;
		int indeks;
	};

	stack<string> prefiksi;
	stack<Elem> stek;
	prefiksi.push("   ");
	stek.push({ koren, 0 });

	while (!stek.empty()) {
		Elem elem = stek.top();
		string prefiks = prefiksi.top();

		if (elem.cvor->DaLiSamList()) {
			return;
		}

		if (elem.indeks == elem.cvor->brojKljuceva) {
			prefiksi.pop();
			stek.pop();
		}
		else {
			stek.pop();
			stek.push({ elem.cvor, elem.indeks + 1 });
		}

		cout << prefiks << elem.indeks/* << " " << (*(elem.cvor))[elem.indeks]*/ << ":";

		for (int i = 0; i < ((Cvor*)((*(elem.cvor))[elem.indeks]))->brojKljuceva; i++) {
			cout << " " << (*((Cvor*)((*(elem.cvor))[elem.indeks])))(i);
		}

		cout << endl;

		if (!(((Cvor*)(*(elem.cvor))[elem.indeks])->DaLiSamList())) {
			stek.push({ ((Cvor*)(*(elem.cvor))[elem.indeks]), 0 });
			prefiksi.push(prefiks + "    ");
		}
	}
}

template <typename Element>
void BPS<Element>::ubaciElement(long long int kljuc, Element podatak) {
	Element* novi = new Element(podatak);

	if (koren == nullptr) {
		koren = new Cvor(m, true);
		koren->ubaciKljuc(kljuc, (void*)novi);
		brojKljuceva = 1;
		popraviKraj();
		return;
	}

	Cvor* temp = koren;

	stack<Cvor*> stek;

	while (!temp->DaLiSamList()) {
		stek.push(temp);
		bool gotov = false;
		for (int i = 0; i < temp->get_brojKljuceva(); i++) {
			if (kljuc < (*temp)(i)) {
				temp = (Cvor*)(*temp)[i];
				gotov = true;
				break;
			}
		}

		if (!gotov) {
			temp = (Cvor*)(*temp)[temp->get_brojKljuceva()];
		}
	} //NASAO SAM GDE TREBA DA UBACIM KLJUC

	// 1. POKUSAJ DA UBACIS U LIST

	// 2. NE MOZEMO DA UBACIMO U LIST:

		// 2.1 LIST JE I KOREN

		// 2.2 LIST NIJE KOREN

	// 3. PROPAGIRAJ KLJUC DO GORE

		// 3.1 UBACUJEMO U CVOR KOJI JESTE KOREN

		// 3.2 UBACUJEMO U CVOR KOJI NIJE KOREN

	//ZAVRSITI

	void* srednjiPodatak = novi;

	Cvor* noviCvor = temp->ubaciKljuc(kljuc, srednjiPodatak);

	while (noviCvor != nullptr) {
		if (stek.empty()) {
			Cvor* noviKoren = new Cvor(m, false);
			koren = noviKoren;
			(*koren)(0) = kljuc;
			(*koren)[0] = temp;
			(*koren)[1] = noviCvor;
			koren->brojKljuceva = 1;
			break;
		}
		else {
			Cvor* otac = stek.top();
			stek.pop();

			//cout << kljuc << " " << (*temp)(0) << " " << (*temp)(1) << " " << (*noviCvor)(0) << " " << (*otac)[0] << " " << noviCvor << " HEJ!" << endl;

			for (int i = 0; i <= otac->get_brojKljuceva(); i++) {
				if ((*otac)[i] == temp) {
					(*otac)[i] = noviCvor;
					//cout << noviCvor << " BRUH" << endl;
					break;
				}
			}

			//cout << kljuc << " " << (*temp)(0) << " " << (*temp)(1) << " " << (*noviCvor)(0) << " " << (*otac)[0] << " HEJ!" << endl;

			noviCvor = otac->ubaciKljuc(kljuc, temp);
			
			//cout << kljuc << " " << (*temp)(0) << " " << (*temp)(1) << " " << 0 << " " << (*otac)[0] << " " << (*otac)[1] << " HEJ!" << endl;

			temp = otac;
		}
	}

	brojKljuceva++;

	popraviKraj();
}

template<typename Element>
void BPS<Element>::izbrisiElement(long long int kljuc){
	if (koren == nullptr) {
		return;
	}

	Cvor* temp = koren;

	stack<Cvor*> stek;
	stack<int> indeksi;
	
	long long int* mestoKljucaUStablu = nullptr;

	bool pronasao = false;

	while (!temp->DaLiSamList()) {
		stek.push(temp);
		bool gotov = false;
		/*if (pronasao == false) {
			mestoKljucaUStablu = nullptr;
		}*/
		for (int i = 0; i < temp->get_brojKljuceva(); i++) {
			if (kljuc <= (*temp)(i)) {
				if (kljuc == (*temp)(i)) {
					mestoKljucaUStablu = &((*temp)(i));
					pronasao = true;
				}
				indeksi.push(i);
				temp = (Cvor*)(*temp)[i];
				gotov = true;
				break;
			}
		}

		if (!gotov) {
			/*if (pronasao == false) {
				mestoKljucaUStablu = &((*temp)(temp->get_brojKljuceva() - 1));
			}*/
			indeksi.push(temp->get_brojKljuceva());
			temp = (Cvor*)(*temp)[temp->get_brojKljuceva()];
		}
	}	// NASAO SAM ODAKLE IZBACUJEM

	// 1. Da li taj kljuc uopste postoji tu

	// 2. Ako postoji, ukloni samo njega ako je moguce

	// 3. Ako nije moguce i koren si, samo ukloni taj kljuc i ako nema vise kljuceva, izbrisi se i stavi koren na nullptr

	// 4. Ako nije moguce, pokusaj da pozajmis od desnog brata

	// 5. Ako nije moguce, pokusaj da pozajmis od levog brata

	// 6. Ako nije moguce, pokusaj da se spojis sa desnim bratom

	// 7. Ako nije moguce, pokusaj da se spojis sa levim bratom

	// Ako 6. i 7. -> 8. Ponovi korake od 3. do 8. za oca ako on vise nema dovoljno kljuceva (gubi jedan kljuc sigurno).

	// POCETAK 1.

	int indeksKljuca = -1;

	for (int i = 0; i < temp->get_brojKljuceva(); i++) {
		if ((*temp)(i) == kljuc) {
			indeksKljuca = i;
		}
	}

	if (indeksKljuca == -1) {
		return;
	}

	// KRAJ 1.

	// POCETAK 2.

	
	delete (Element*)(*temp)[indeksKljuca];

	for (int j = indeksKljuca; j < temp->get_brojKljuceva() - 1; j++) {
		(*temp)(j) = (*temp)(j + 1);
		(*temp)[j] = (*temp)[j + 1];
	}

	(*temp)[temp->get_brojKljuceva() - 1] = (*temp)[temp->get_brojKljuceva()];

	if (temp->DaLiSamList() && temp->get_brojKljuceva() > 1 && indeksKljuca == temp->get_brojKljuceva() - 1 && mestoKljucaUStablu != nullptr) {
		(*mestoKljucaUStablu) = (*temp)(temp->get_brojKljuceva() - 2);
	}

	(temp->brojKljuceva)--;
	brojKljuceva--;

	if (temp->get_brojKljuceva() >= temp->minimalanBrojElemenata()) {
		return;
	}

	// KRAJ 2.

	// POCETAK 3

	if (stek.empty()) {
		if (brojKljuceva == 0) {
			delete koren;
			koren = nullptr;
		}

		return;
	}

	// KRAJ 3

	Cvor* otac = stek.top();
	stek.pop();

	int indeks = indeksi.top();
	indeksi.pop();

	// POCETAK 4.

	if (indeks != otac->brojKljuceva) {

		Cvor* desniBrat = (Cvor*)(*otac)[indeks + 1];

		if (desniBrat->brojKljuceva != desniBrat->minimalanBrojElemenata()) {
			(*otac)(indeks) = (*desniBrat)(0);

			(*temp)(temp->brojKljuceva) = (*desniBrat)(0);
			(*temp)[temp->brojKljuceva] = (*desniBrat)[0];

			for (int j = 0; j < desniBrat->get_brojKljuceva() - 1; j++) {
				(*desniBrat)(j) = (*desniBrat)(j + 1);
				(*desniBrat)[j] = (*desniBrat)[j + 1];
			}

			(*desniBrat)[desniBrat->get_brojKljuceva() - 1] = (*temp)[desniBrat->get_brojKljuceva()];

			(desniBrat->brojKljuceva)--;
			(temp->brojKljuceva)++;

			return;
		}
	}

	// KRAJ 4.

	// POCETAK 5.

	if (indeks != 0) {

		Cvor* leviBrat = (Cvor*)(*otac)[indeks - 1];

		if (leviBrat->brojKljuceva != leviBrat->minimalanBrojElemenata()) {
			(*otac)(indeks - 1) = (*leviBrat)(leviBrat->brojKljuceva - 2);

			for (int i = temp->brojKljuceva - 1; i > 0; i--) {
				(*temp)(i) = (*temp)(i - 1);
				(*temp)[i] = (*temp)[i - 1];
			}

			(*temp)(0) = (*leviBrat)(leviBrat->brojKljuceva - 1);
			(*temp)[0] = (*leviBrat)[leviBrat->brojKljuceva - 1];

			if (mestoKljucaUStablu != nullptr) {
				(*mestoKljucaUStablu) = (*temp)(temp->brojKljuceva);
			}

			(leviBrat->brojKljuceva)--;
			(temp->brojKljuceva)++;

			return;
		}
	}

	// KRAJ 5.

	// POCETAK 6.

	if (indeks != otac->brojKljuceva) {
		Cvor* desniBrat = (Cvor*)(*otac)[indeks + 1];

		// *** Reroutovanje pokazivaca ulancane liste

		Cvor* pocetakListe = koren;

		while (!(pocetakListe->DaLiSamList())) {
			pocetakListe = (Cvor*)(*pocetakListe)[0];
		}

		if (pocetakListe != temp) {
			while ((*pocetakListe)[m - 1] != temp) {
				pocetakListe = (Cvor*)(*pocetakListe)[m - 1];
			}
			(*pocetakListe)[m - 1] = desniBrat;
		}

		// ***
	
		for (int i = desniBrat->brojKljuceva - 1; i >= 0; i--) {
			(*desniBrat)(i + temp->brojKljuceva) = (*desniBrat)(i);
			(*desniBrat)[i + temp->brojKljuceva] = (*desniBrat)[i];
		}
		
		for (int i = 0; i < temp->brojKljuceva; i++) {
			(*desniBrat)(i) = (*temp)(i);
			(*desniBrat)[i] = (*temp)[i];
		}

		for (int i = indeks; i < otac->brojKljuceva; i++) {
			(*otac)(i) = (*otac)(i + 1);
			(*otac)[i] = (*otac)[i + 1];
		}

		desniBrat->brojKljuceva += temp->brojKljuceva;

		(otac->brojKljuceva)--;

		delete temp;
		// PRELAZ U FAZU 8
		stek.push(otac);
		propagirajBrisanje(stek, indeksi);

		return;
	}

	// KRAJ 6.

	// POCETAK 7.

	if (indeks != 0) {
		Cvor* leviBrat = (Cvor*)(*otac)[indeks - 1];

		// *** Reroutovanje pokazivaca ulancane liste

		Cvor* pocetakListe = koren;

		while (!(pocetakListe->DaLiSamList())) {
			pocetakListe = (Cvor*)(*pocetakListe)[0];
		}

		if (pocetakListe != leviBrat) {
			while ((*pocetakListe)[m - 1] != leviBrat) {
				pocetakListe = (Cvor*)(*pocetakListe)[m - 1];
			}
			(*pocetakListe)[m - 1] = temp;
		}

		// ***

		for (int i = temp->brojKljuceva - 1; i >= 0; i--) {
			(*temp)(i + leviBrat->brojKljuceva) = (*temp)(i);
			(*temp)[i + leviBrat->brojKljuceva] = (*temp)[i];
		}

		for (int i = 0; i < leviBrat->brojKljuceva; i++) {
			(*temp)(i) = (*leviBrat)(i);
			(*temp)[i] = (*leviBrat)[i];
		}

		for (int i = indeks - 1; i < otac->brojKljuceva; i++) {
			(*otac)(i) = (*otac)(i + 1);
			(*otac)[i] = (*otac)[i + 1];
		}		

		temp->brojKljuceva += leviBrat->brojKljuceva;

		(otac->brojKljuceva)--;

		delete leviBrat;

		// PRELAZ U FAZU 8
		stek.push(otac);
		propagirajBrisanje(stek, indeksi);

		return;
	}

	// KRAJ 7.

	cout << "GRESKA!" << endl;
	exit(1);
}

template <typename Element>
void BPS<Element>::propagirajBrisanje(stack<Cvor*>& stek, stack<int>& indeksi) {	//FAZA 8
	Cvor* temp = stek.top();
	stek.pop();

	while (true) {	

		if (stek.empty() && temp->brojKljuceva == 0) { // Ako je temp koren i prazan je, samo ga izbrisi i postavi njegovog sina za koren
			//cout << "HEJ";
			koren = (Cvor*)(*temp)[0];
			//cout << ((Cvor*)(*temp)[0])->DaLiSamList();
			delete temp;
			return;
		}

		if (stek.empty() || temp->brojKljuceva >= temp->minimalanBrojElemenata()) {
			return;
		}

		Cvor* otac = stek.top();
		stek.pop();
		int indeks = indeksi.top();
		indeksi.pop();

		//POZAJMI OD DESNOG

		if (indeks != otac->brojKljuceva) {
			Cvor* desniBrat = (Cvor*)(*otac)[indeks + 1];			
			if (desniBrat->brojKljuceva != desniBrat->minimalanBrojElemenata()) {
				(*temp)(temp->brojKljuceva) = (*otac)(indeks);
				(*temp)[temp->brojKljuceva + 1] = (*desniBrat)[0];
				(*otac)(indeks) = (*desniBrat)(0);
				for (int i = 0; i < desniBrat->brojKljuceva - 1; i++) {
					(*desniBrat)(i) = (*desniBrat)(i + 1);
					(*desniBrat)[i] = (*desniBrat)[i + 1];
				}
				(*desniBrat)[desniBrat->brojKljuceva - 1] = (*desniBrat)[desniBrat->brojKljuceva];

				(desniBrat->brojKljuceva)--;
				(temp->brojKljuceva)++;

				temp = otac;
				continue;
			}
		}



		//POZAJMI OD LEVOG

		if (indeks != 0) {
			Cvor* leviBrat = (Cvor*)(*otac)[indeks - 1];

			if (leviBrat->brojKljuceva != leviBrat->minimalanBrojElemenata()) {
				(*temp)[temp->brojKljuceva + 1] = (*temp)[temp->brojKljuceva];

				for (int i = temp->brojKljuceva; i > 0; i--) {
					(*temp)(i) = (*temp)(i - 1);
					(*temp)[i] = (*temp)[i - 1];
				}

				(*temp)(0) = (*otac)(indeks - 1);
				(*temp)[0] = (*leviBrat)[leviBrat->brojKljuceva];

				(*otac)(indeks - 1) = (*leviBrat)(leviBrat->brojKljuceva - 1);

				(leviBrat->brojKljuceva)--;
				(temp->brojKljuceva)++;

				temp = otac;
				continue;
			}
		}


		//SPOJI SA DESNIM

		if (indeks != otac->brojKljuceva) {
			Cvor* desniBrat = (Cvor*)(*otac)[indeks + 1];

			(*desniBrat)[desniBrat->brojKljuceva + temp->brojKljuceva + 1] = (*desniBrat)[desniBrat->brojKljuceva];
			
			for (int i = 0; i < desniBrat->brojKljuceva; i++) {
				(*desniBrat)(i + temp->brojKljuceva + 1) = (*desniBrat)(i);
				(*desniBrat)[i + temp->brojKljuceva + 1] = (*desniBrat)[i];
			}

			(*desniBrat)[0] = (*temp)[0];

			(*desniBrat)(temp->brojKljuceva) = (*otac)(indeks);
			(*desniBrat)[temp->brojKljuceva] = (*temp)[temp->brojKljuceva];

			for (int i = 0; i < temp->brojKljuceva; i++) {
				(*desniBrat)(i) = (*temp)(i);
				(*desniBrat)[i] = (*temp)[i];
			}

			for (int i = indeks; i < otac->brojKljuceva; i++) {
				(*otac)(i) = (*otac)(i + 1);
				(*otac)[i] = (*otac)[i + 1];
			}
			(*otac)[otac->brojKljuceva] = (*otac)[otac->brojKljuceva + 1];

			(otac->brojKljuceva)--;

			desniBrat->brojKljuceva += temp->brojKljuceva + 1;

			delete temp;
			temp = otac;

			continue;
		}

		//SPOJI SA LEVIM

		if (indeks != 0) { // POTENCIJALNO NISTA NE RADI
			Cvor* desniBrat = temp;
			temp = (Cvor*)(*otac)[indeks - 1];

			(*desniBrat)[desniBrat->brojKljuceva + temp->brojKljuceva + 1] = (*desniBrat)[desniBrat->brojKljuceva];

			for (int i = 0; i < desniBrat->brojKljuceva; i++) {
				(*desniBrat)(i + temp->brojKljuceva + 1) = (*desniBrat)(i);
				(*desniBrat)[i + temp->brojKljuceva + 1] = (*desniBrat)[i];
			}

			(*desniBrat)[0] = (*temp)[0];

			(*desniBrat)(temp->brojKljuceva) = (*otac)(indeks);
			(*desniBrat)[temp->brojKljuceva] = (*temp)[temp->brojKljuceva];

			for (int i = 0; i < temp->brojKljuceva; i++) {
				(*desniBrat)(i) = (*temp)(i);
				(*desniBrat)[i] = (*temp)[i];
			}

			for (int i = indeks; i < otac->brojKljuceva; i++) {
				(*otac)(i) = (*otac)(i + 1);
				(*otac)[i] = (*otac)[i + 1];
			}
			(*otac)[otac->brojKljuceva] = (*otac)[otac->brojKljuceva + 1];

			(otac->brojKljuceva)--;

			desniBrat->brojKljuceva += temp->brojKljuceva + 1;

			delete temp;
			temp = otac;

			continue;
		}
		
	}
}

template <typename Element>
BPS<Element>::~BPS() {
	if (brojKljuceva == 0) {
		return;
	}

	queue<Cvor*> red;

	if (koren != nullptr) {
		red.push(koren);
		koren = nullptr;
	}

	while (!red.empty()) {
		Cvor* cv = red.front();
		red.pop();

		if (cv->DaLiSamList()) {
			//cout << cv->get_brojKljuceva() << " " << (*cv)(0) << endl;
			for (int i = 0; i < cv->get_brojKljuceva(); i++) {
				//cout << *((Element*)((*cv)[i])) << endl;
				delete ((Element*)((*cv)[i]));
			}
		}
		else {
			for (int i = 0; i <= cv->get_brojKljuceva(); i++) {
				red.push((Cvor*)(*cv)[i]);
			}
		}

		delete cv;
	}
}
