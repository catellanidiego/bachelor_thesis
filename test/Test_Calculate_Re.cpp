#include <cmath>
#include "Calculate_Re.hpp"
#include "Is_close.hpp"

int main() {
	int res = EXIT_SUCCESS;
	double v = 0.0;
	double r = 0.0;
	double rho = 1.204;
	double eta = 1.81e-5;
	double Re = Calculate_Re(v, r, rho, eta);
	bool test_1 = is_close(Re, 0.0, 1e-6, 1e-6);
	if (test_1 == 0) {res = EXIT_FAILURE;}

	r = 1.0;
	Re = Calculate_Re(v, r, rho, eta);
	bool test_2 = is_close(Re, 0.0, 1e-6, 1e-6);
	if (test_2 == 0) {res = EXIT_FAILURE;}

	v = 1.0;
	Re = Calculate_Re(v, r, rho, eta);
	bool test_3 = is_close(Re, 133038.67403, 1e-6, 1e-6);
	if (test_3 == 0) {res = EXIT_FAILURE;}

	return res;
}