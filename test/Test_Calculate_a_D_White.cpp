#include "../include/Calculate_a_D_White.hpp"
#include <cmath>
int main() {
	int res = EXIT_SUCCESS;
	double epsilon = 1e-6;
	double r = 0.01;
	double A = M_PI*r*r;
	double m = 0.1;
	double v = 1.0;
	//Re calculated to be 1330.39
	double a_D_White = Calculate_a_D_White(v, r, A, m);
	if (std::abs(a_D_White + 0.00109342) > epsilon) {
		res = EXIT_FAILURE;
	}

	return res;
}