#include "podatak.h"

ostream& operator<<(ostream& os, const Podatak& pod){
	os << setprecision(2) << fixed << pod.CA_ID << "|" << pod.CA_B_ID << "|" << pod.CA_C_ID << "|" << pod.CA_NAME << "|" << pod.CA_TAX_ST << "|" << pod.CA_BAL;
	return os;
}
