#include "../include/Calculate_Re.hpp"
#include <cmath>
int main() {
	int res = EXIT_SUCCESS;
	double epsilon = 1e-5;
	double v = 0.0;
	double r = 0.0;
	double Re = Calculate_Re(v, r);
	if (std::abs(Re) > epsilon) {
		res = EXIT_FAILURE;
	}
	r = 1.0;
	Re = Calculate_Re(v, r);
	if (std::abs(Re) > epsilon) {
		res = EXIT_FAILURE;
	}
	v = 1.0;
	Re = Calculate_Re(v, r);
	if (std::abs(Re - 133038.67403) > epsilon) {
		res = EXIT_FAILURE;
	}
	return res;
}