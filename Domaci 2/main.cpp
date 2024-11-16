#include "BPlusStablo.h";



bool ucitajBazu(BPS<Podatak>& stablo, string imeFajla) {
	ifstream fajl(imeFajla);

	if(!fajl.is_open()){
		return false;
	}

	while (!fajl.eof()) {
		long long int CA_ID, CA_ID_B, CA_ID_C, CA_TAX_ST;
		double CA_BAL;
		string CA_NAME = "";
		char chr;

		fajl >> std::noskipws >> CA_ID >> chr >> CA_ID_B >> chr >> CA_ID_C >> chr;

		if (fajl.eof()) {
			break;
		}

		fajl >> std::noskipws >> chr;

		if (fajl.eof()) {
			break;
		}

		while (chr != '|') {
			CA_NAME += chr;
			fajl >> std::noskipws >> chr;
		}

		fajl >> std::noskipws >> CA_TAX_ST >> chr >> CA_BAL;

		stablo.ubaciElement(CA_ID, Podatak(CA_ID, CA_ID_B, CA_ID_C, CA_NAME, CA_TAX_ST, CA_BAL));

		if (!fajl.eof()) {
			fajl >> std::noskipws >> chr;
		}
		else {
			break;
		}

	}

	fajl.close();

	return true;
}

int main() {
	cout << "POCETAK" << endl;
	
	/* {
		BPS<Podatak> stablo(6);

		ucitajBazu(stablo, "CustomerAccount2500.txt");

		stablo.ubaciElement(0, Podatak(0, 0, 0, "HEJ1", 0, 0.0));
		stablo.ubaciElement(1, Podatak(0, 0, 0, "HEJ2", 0, 0.0));

		stablo.ubaciElement(2, Podatak(0, 0, 0, "HEJ3", 0, 0.0));

		stablo.izbrisiElement(2);

		stablo.ubaciElement(43000005002, Podatak(0, 0, 0, "HEJ4", 0, 0.0));
		stablo.ubaciElement(43000005003, Podatak(0, 0, 0, "HEJ5", 0, 0.0));

		stablo.ubaciElement(43000005004, Podatak(0, 0, 0, "HEJ6", 0, 0.0));

		stablo.izbrisiElement(43000005004);

		stablo.ispisi();
		stablo.ispisiSekvencijalno();

		cout << stablo.pronadjiElementeSekvencijalne(0, 10) << endl;

	}*/
	{
	cout << "Dobar dan." << endl;

	int m;

	bool dobrom = false;

	while (!dobrom) {
		cout << "Unesite stepen B+ stabla: " << endl;

		cin >> m;
		if (m >= 3) {
			dobrom = true;
		}
		else {
			cout << "Niste uneli validnu vrednost za stepen B+ stabla." << endl;
		}
	}

	BPS<Podatak> stablo(m);

	string imeBaze;

	bool izabranaBaza = false;
	while (!izabranaBaza) {
		int baza;
		cout << "Unesite ime zeljene baze:" << endl;

		cin >> imeBaze;
		izabranaBaza = ucitajBazu(stablo, imeBaze);

		if (izabranaBaza == false) {
			cout << "Baza ne postoji." << endl;
		}
	}

	bool zavrsi = false;

	while (!zavrsi) {
		char izbor = '0';

		cout << endl;
		cout << endl;
		cout << "Unesite zeljenu operaciju:" << endl;
		cout << "1. Ispisi indeksno stablo baze;" << endl;
		cout << "2. Ispisi bazu;" << endl;
		cout << "3. Upisi red u bazu;" << endl;
		cout << "4. Izbrisi red iz baze;" << endl;
		cout << "5. Pretrazi jedan kljuc;" << endl;
		cout << "6. Pretrazi vise razlicitih kljuceva;" << endl;
		cout << "7. Pretrazi vise sekvencijalnih kljuceva;" << endl;
		cout << "0. Zavrsi program." << endl;

		cin >> izbor;

		switch (izbor) {
		case '1': {
			stablo.ispisi();
			break;
		}
		case '2': {
			stablo.ispisiSekvencijalno();
			break;
		}
		case '3': {
			long long int ID, ID_B, ID_C, TAX;
			string NAME;
			double BAL;

			cout << "Upisite CA_ID: ";
			cin >> ID;
			cout << "Upisite CA_B_ID: ";
			cin >> ID_B;
			cout << "Upisite CA_C_ID: ";
			cin >> ID_C;
			cin.ignore(1, '\n');
			cout << "Upisite CA_NAME: ";
			getline(cin, NAME, '\n');

			cout << "Upisite CA_TAX_ST: ";
			cin >> TAX;
			cout << "Upisite CA_BAL: ";
			cin >> BAL;

			stablo.ubaciElement(ID, Podatak(ID, ID_B, ID_C, NAME, TAX, BAL));

			break;
		}
		case '4': {
			long long int ID;

			cout << "Upisite CA_ID: ";
			cin >> ID;
			stablo.izbrisiElement(ID);
			break;
		}
		case '5': {
			long long int ID;

			cout << "Upisite CA_ID: ";
			cin >> ID;
			int brKoraka;

			Podatak* pod = stablo.pronadjiElementOdredjenKljucem(ID, brKoraka);

			if (pod != nullptr) {
				cout << *pod << endl;
			}
			else {
				cout << "Nismo pronasli element sa datim ID-om." << endl;
			}

			cout << "Pretraga je izvrsena u " << brKoraka << " koraka." << endl;
			break;
		}
		case '6': {
			cout << "Upisite broj elemenata koje pretrazujete: ";
			int n;
			cin >> n;

			if (n < 1) {
				cout << "Ne validan broj kljuceva." << endl;
				break;
			}

			long long int* niz = new long long int[n];

			for (int i = 0; i < n; i++) {
				cout << "Upisite CA_ID " << i + 1 << ": ";
				long long int id;
				cin >> id;

				niz[i] = id;
			}

			int brKoraka = stablo.pronadjiElemente(niz, n);

			cout << "Pretraga je izvrsena u " << brKoraka << " koraka." << endl;

			delete[] niz;
			break;
		}
		case '7': {
			cout << "Upisite broj elemenata koje pretrazujete: ";
			int n;
			cin >> n;

			if (n < 1) {
				cout << "Ne validan broj kljuceva." << endl;
				break;
			}

			long long int id;
			cout << "Upisite pocetni CA_ID: ";
			cin >> id;

			int brKoraka = stablo.pronadjiElementeSekvencijalne(id, n);

			cout << "Pretraga je izvrsena u " << brKoraka << " koraka." << endl;

			break;
		}
		case '0': {
			zavrsi = true;
			cout << "Pozdrav!" << endl;
			break;
		}
		default: {
			cout << "Izabrana operacija ne postoji." << endl;
			break;
		}
		}
		cout << endl;
		cout << endl;
	}
	}
	cout << "KRAJ" << endl;
}