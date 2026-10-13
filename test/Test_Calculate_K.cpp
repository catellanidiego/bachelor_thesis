#include <cmath>
#include <iostream>
#include "../include/Calculate_K.hpp"
int main() {
	int res = EXIT_SUCCESS;
	double epsilon = 1e-12;
	double m = 0.0;
	double v = 2.0;
	double K = Calculate_K(v, m);
	if (std::abs(K) > epsilon) {
		res = EXIT_FAILURE;
		std::cout << "a" << std::endl;
	}
	m = 1.0;
	K = Calculate_K(v, m);
	if (std::abs(K - 2.0) > epsilon) {
		res = EXIT_FAILURE;
		std::cout << "a" << std::endl;
	}
	v = -2.0;
	K = Calculate_K(v, m);
	if (std::abs(K - 2.0) > epsilon) {
		res = EXIT_FAILURE;
		std::cout << "a" << std::endl;
	}
	return res;
}