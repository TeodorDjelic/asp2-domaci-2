#pragma once
#include "biblioteke.h"

struct Podatak{
//CA_ID, CA_B_ID, CA_C_ID, CA_NAME, CA_TAX_ST, CA_BAL
private:
	/*struct IDstruct {
		int ID;
		IDstruct* slID;

		IDstruct(int ID) : ID(ID) {}
	};

	static IDstruct* idovi;*/

	long long int CA_ID;
	long long int CA_B_ID;
	long long int CA_C_ID;
	std::string CA_NAME;
	long long int CA_TAX_ST;
	double CA_BAL;
public:
	Podatak() = delete;
	Podatak(const Podatak& podatak) : CA_ID(podatak.CA_ID), CA_B_ID(podatak.CA_B_ID), CA_C_ID(podatak.CA_C_ID), CA_NAME(podatak.CA_NAME), CA_TAX_ST(podatak.CA_TAX_ST), CA_BAL(podatak.CA_BAL) {}

	explicit Podatak(long long int CA_ID, long long int CA_B_ID, long long int CA_C_ID, std::string CA_NAME, long long int CA_TAX_ST, double CA_BAL) : CA_ID(CA_ID), CA_B_ID(CA_B_ID), CA_C_ID(CA_C_ID), CA_NAME(CA_NAME), CA_TAX_ST(CA_TAX_ST), CA_BAL(CA_BAL) {}
	
	friend ostream& operator<<(ostream& os, const Podatak& pod);

	long long int get_CA_ID() {
		return CA_ID;
	}

	long long int get_CA_B_ID() {
		return CA_B_ID;
	}

	long long int get_CA_C_ID() {
		return CA_C_ID;
	}

	std::string get_CA_NAME() {
		return CA_NAME;
	}

	long long int get_CA_TAX_ST() {
		return CA_TAX_ST;
	}

	double get_CA_BAL() {
		return CA_BAL;
	}

	int set_CA_B_ID(int CA_B_ID) {
		this->CA_B_ID = CA_B_ID;
		return 0;
	}

	int set_CA_C_ID(int CA_C_ID) {
		this->CA_C_ID = CA_C_ID;
		return 0;
	}

	int set_CA_NAME(std::string CA_NAME) {
		this->CA_NAME = CA_NAME;
		return 0;
	}

	int set_CA_TAX_ST(int CA_TAX_ST) {
		this->CA_TAX_ST = CA_TAX_ST;
		return 0;
	}

	int set_CA_BAL(double CA_BAL) {
		this->CA_BAL = CA_BAL;
		return 0;
	}

	~Podatak() {

	}
};