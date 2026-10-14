#include <cmath>
#include "Calculate_a_Coulomb.hpp" 
#include "Is_close.hpp"

int main() {
	int res = EXIT_SUCCESS;
	double mu_d = 1.0;
	double v = 1.0;
	double s = 0.0;
	double R = 1.0;
	double a_Coulomb = Calculate_a_Coulomb(mu_d, v, s, R);
	bool test_2 = is_close(a_Coulomb, -10.06, 1e-4, 1e-4);
	if (test_2 == 0) {res = EXIT_FAILURE;}
	
	return res;
}