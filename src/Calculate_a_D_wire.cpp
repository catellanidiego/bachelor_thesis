#include "Calculate_C_D_wire.hpp"
#include "Calculate_p_f.hpp"
#include "Calculat_a_D_wire.hpp"

double Calculate_a_D_wire(double R, double s, double v, double D, double m, double rho, double eta) {
	double p_f = Calculate_p_f(R, s);
	if (p_f < 1e-6) {return 0.0;}
	double omega = v/p_f;
	int N = 100;
	double dp = p_f/N;
	double integral_sum = 0.0;
	for (int i = 0; i < N; i++) {
		double p = (i + 0.5)*dp;
		double v_local = std::abs(p*omega);
		double C_D_local = Calculate_C_D_wire(v_local, D, rho, eta);
		integral_sum += C_D_local*p*p*(p/p_f)*dp;
	}
	double a_D_wire = 0.5*rho*omega*omega*D*integral_sum/m; //wire's mass is negligible compared to the sphere's mass
	if (v > 0) {
		a_D_wire = -a_D_wire;
	}
	return a_D_wire;
}