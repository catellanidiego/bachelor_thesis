#include <cmath>
#include "Calculate_K.hpp"
#include "Is_close.hpp"

int main() {
	int res = EXIT_SUCCESS;
	double m = 0.0;
	double v = 2.0;
	double K = Calculate_K(v, m);
	bool test_1 = is_close(K, 0.0, 1e-6, 1e-6);
	if (test_1 == 0) {res = EXIT_FAILURE;}

	m = 1.0;
	K = Calculate_K(v, m);
	bool test_2 = is_close(K, 2.0, 1e-6, 1e-6);
	if (test_2 == 0) {res = EXIT_FAILURE;}

	v = -2.0;
	K = Calculate_K(v, m);
	bool test_3 = is_close(K, 2.0, 1e-6, 1e-6);
	if (test_3 == 0) {res = EXIT_FAILURE;}
	
	return res;
}