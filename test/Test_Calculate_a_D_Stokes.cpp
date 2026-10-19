#include <cmath>
#include "Calculate_a_D_sphere_Stokes.hpp"
#include "Is_close.hpp"

int main() {
	int res = EXIT_SUCCESS;
	double r = 0.01;
	double m = 0.1;
	double v = 5e-4;
	double eta = 1.81e-5;
	//Re calculated to be 0.665193

	double a_D_sphere_Stokes = Calculate_a_D_sphere_Stokes(v, r, m, eta);
	bool test_1 = is_close(a_D_sphere_Stokes, -1.70588e-8, 1e-6, 1e-6);
	if (test_1 == 0) {res = EXIT_FAILURE;}

	return res;
}