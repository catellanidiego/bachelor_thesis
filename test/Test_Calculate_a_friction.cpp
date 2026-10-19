#include <cmath>
#include "Calculate_a_friction.hpp" 
#include "Is_close.hpp"

int main() {
	int res = EXIT_SUCCESS;
	double mu_eq = 1.0;
	double v = 1.0;
	double s = 0.0;
	double R = 1.0;
	double epsilon = 1e-6;
	double g = 9.81;
	double a_friction = Calculate_a_friction(mu_eq, v, s, R, epsilon, g);
	bool test_2 = is_close(a_friction, -10.06, 1e-4, 1e-4);
	if (test_2 == 0) {res = EXIT_FAILURE;}
	
	return res;
}