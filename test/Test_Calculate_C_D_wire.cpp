#include "Calculate_C_D_wire.hpp"
#include "Is_close.hpp"
int main() {
	int res = EXIT_SUCCESS;
	double D = 0.00028;
	double v = 1e-7;
	double rho = 1.204;
	double eta = 1.81e-5;
	//1e-8 < Re <= 1e-4
	double C_D_wire = Calculate_C_D_wire(v, D, rho, eta);
	bool test_1 = is_close(C_D_wire, 205049056.927917 , 1e-6, 1e-6);
	if (test_1 == 0) {res = EXIT_FAILURE;}
	
	v = 1.0;
	//1e-4 < Re < 2e5
	C_D_wire = Calculate_C_D_wire(v, D, rho, eta);
	bool test_2 = is_close(C_D_wire, 2.130338, 1e-6, 1e-6);
	if (test_2 == 0) {res = EXIT_FAILURE;}

	v = 20000;
	//Re >= 2e5
	C_D_wire = Calculate_C_D_wire(v, D, rho, eta);
	bool test_3 = is_close(C_D_wire, 0.3, 1e-6, 1e-6);
	if (test_3 == 0) {res = EXIT_FAILURE;}
	return res;
}