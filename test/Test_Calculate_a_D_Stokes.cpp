#include "../include/Calculate_a_D_Stokes.hpp"
#include <cmath>
int main() {
	int res = EXIT_SUCCESS;
	double epsilon = 1e-6;
	double r = 0.01;
	double m = 0.1;
	double v = 5e-4;
	//Re calculated to be 0.665193
	double a_D_Stokes = Calculate_a_D_Stokes(v, r, m);
	if (std::abs(a_D_Stokes + 1.70588e-8) > epsilon) {
		res = EXIT_FAILURE;
	}
	return res;
}