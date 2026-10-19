#include <cmath>
#include "Calculate_U.hpp"
#include "Is_close.hpp"

int main() {
	int res = EXIT_SUCCESS;
	double m = 0.0;
	double h = 0.0;
	double g = 9.81;
	double U = Calculate_U(h, m, g);
	bool test_1 = is_close(U, 0.0, 1e-6, 1e-6);
	if (test_1 == 0) {res = EXIT_FAILURE;}
	
	m = 1.0;
	U = Calculate_U(h, m, g);
	bool test_2 = is_close(U, 0.0, 1e-6, 1e-6);
	if (test_2 == 0) {res = EXIT_FAILURE;}
	
	h = 1.0;
	U = Calculate_U(h, m, g);
	bool test_3 = is_close(U, 9.81, 1e-3, 1e-3);
	if (test_3 == 0) {res = EXIT_FAILURE;}
	
	h = 2.0;
	U = Calculate_U(h, m, g);
	bool test_4 = is_close(U, 19.62, 1e-4, 1e-4);
	if (test_4 == 0) {res = EXIT_FAILURE;}

	return res;
}