#include "../include/Calculate_a_D_wire.hpp"
#include "../include/Is_close.hpp"

int main() {
	int res = EXIT_SUCCESS;
	double R = 0.08;
	double s = 0.2;
	double v = 0.2;
	double D = 2.8e-4;
	double m = 0.08;
	double a_D_wire_estimate = Calculate_a_D_wire(R, s, v, D, m);

	double rho = 1.204;
	double p_f = std::pow(16*R*R - s*s, 0.5);
	if (p_f < 1e-6) {return 0.0;}
	double omega = v/p_f;
	int N = 1000000;
	double dp = p_f / N;
	double integral_sum = 0.0;
	for (int i = 0; i < N; i++) {
		double p = (i + 0.5)*dp;
		double v_local = std::abs(p*omega);
		double C_D_local = Calculate_C_D_wire(v_local, D);
		integral_sum += C_D_local*p*p*dp;
	}
	double a_D_wire_exact = 0.5*rho*omega*omega*D*integral_sum/m;
	if (v > 0) {
		a_D_wire_exact = -a_D_wire_exact;
	}
	bool test_1 = is_close(a_D_wire_estimate, a_D_wire_exact, 1e-6, 1e-6);
	if (test_1 == 0) {res = EXIT_FAILURE;}
	return res;
}