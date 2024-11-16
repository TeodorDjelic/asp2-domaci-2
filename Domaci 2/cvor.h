#pragma once
#include "biblioteke.h"
using namespace std;

class Cvor {
private:
	void** pokazivaci;
	long long int* kljucevi;
	int m;
	bool daLiSamList;
public:
	long long int brojKljuceva;
	Cvor() = delete;
	explicit Cvor(int m, bool daLiSamList);

	bool DaLiSamList() {
		return daLiSamList;
	}

	int minimalanBrojElemenata() {
		if (daLiSamList) {
			return floor(((float)m) / 2.0f);
		}
		else {
			return ceil(((float)m) / 2.0f) - 1;
		}
	}

	//Objekat* pronadjiPodatak(int kljuc);

	~Cvor() {
		delete[] pokazivaci;
		delete[] kljucevi;
		pokazivaci = nullptr;
		kljucevi = nullptr;
	}

	//int ubaciKljuc(int kljuc, void*& podatak);

	//Cvor* split();

	Cvor* ubaciKljuc(long long int& kljuc, void* podatak); //pametna

	//int izbaciKljuc(long long int kljuc); //glupa

	int get_brojKljuceva() {
		return brojKljuceva;
	}

	long long int& operator()(const int& i);

	void*& operator[](const int& i);
};