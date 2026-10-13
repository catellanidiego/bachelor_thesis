#include "../include/Calculate_a_Coulomb.hpp"
#include <cmath>
int main() {
	int res = EXIT_SUCCESS;
	double epsilon = 1e-5;
	double mu_d = 0.0;
	double v = 0.0;
	double s = 0.0;
	double R = 0.0;
	double a_Coulomb = Calculate_a_Coulomb(mu_d, v, s, R);
	if (std::abs(a_Coulomb) > epsilon) {
		res = EXIT_FAILURE;
	}
	mu_d = 1.0;
	v = 1.0;
	R = 1.0;
	a_Coulomb = Calculate_a_Coulomb(mu_d, v, s, R);
	if (std::abs(a_Coulomb + 10.06) > epsilon) {
		res = EXIT_FAILURE;
	}
	
	return res;
}