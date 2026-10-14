#include <cmath>
#include "Calculate_a_D_White.hpp"
#include "Is_close.hpp"

int main() {
	int res = EXIT_SUCCESS;
	double r = 0.01;
	double A = M_PI*r*r;
	double m = 0.1;
	double v = 1.0;
	//Re calculated to be 1330.39

	double a_D_White = Calculate_a_D_White(v, r, A, m);
	bool test_1 = is_close(a_D_White, -0.00109342, 1e-6, 1e-6);
	if (test_1 == 0) {res = EXIT_FAILURE;}

	return res;
}