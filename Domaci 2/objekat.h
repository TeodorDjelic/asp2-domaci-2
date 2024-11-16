#pragma once
#include "biblioteke.h"

class Objekat {
private:
	bool daLiSamCvor;
protected:
	explicit Objekat(bool daLiSamCvor) : daLiSamCvor(daLiSamCvor) {}
public:
	Objekat() = delete;
	Objekat(Objekat&) = delete;
	Objekat(Objekat&&) = delete;

	bool DaLiSamCvor() {
		return daLiSamCvor;
	}
};