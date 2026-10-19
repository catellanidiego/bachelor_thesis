#include <cmath>
#include "Calculate_a_D_sphere_no_Stokes.hpp"
#include "Calculate_C_D_sphere_White.hpp"
#include "Is_close.hpp"

int main() {
	int res = EXIT_SUCCESS;
	double r = 0.01;
	double A = M_PI*r*r;
	double m = 0.1;
	double v = 1.0;
	double rho = 1.204;
	double eta = 1.81e-5;
	//Re calculated to be 1330.39

	double C_D_sphere = Calculate_C_D_sphere_White(v, r, rho, eta);
	double a_D_sphere = Calculate_a_D_sphere_no_Stokes(v, C_D_sphere, A, m, rho);
	bool test_1 = is_close(a_D_sphere, -0.00109342, 1e-6, 1e-6);
	if (test_1 == 0) {res = EXIT_FAILURE;}

	return res;
}