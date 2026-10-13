#include "../include/Calculate_U.hpp"
#include <cmath>
int main() {
	int res = EXIT_SUCCESS;
	double epsilon = 1e-12;
	double m = 0.0;
	double h = 0.0;
	double U = Calculate_U(h, m);
	if (std::abs(U) > epsilon) {
		res = EXIT_FAILURE;
	}
	m = 1.0;
	U = Calculate_U(h, m);
	if (std::abs(U) > epsilon) {
		res = EXIT_FAILURE;
	}	
	h = 1.0;
	U = Calculate_U(h, m);
	if (std::abs(U - 9.81) > epsilon) {
		res = EXIT_FAILURE;
	}
	h = 2.0;
	U = Calculate_U(h, m);
	if (std::abs(U - 19.62) > epsilon) {
		res = EXIT_FAILURE;
	}
	return res;
}