#pragma once
#include "Calculate_C_D_wire.hpp"

inline double Calculate_a_D_wire(const double R, const double s, const double v, const double D, const double m, const double rho, const double eta) {
	double p_f = std::pow(16*R*R - s*s, 0.5);
	if (p_f < 1e-6) {return 0.0;}
	double omega = v/p_f;
	int N = 100;
	double dp = p_f/N;
	double integral_sum = 0.0;
	for (int i = 0; i < N; i++) {
		double p = (i + 0.5)*dp;
		double v_local = std::abs(p*omega);
		double C_D_local = Calculate_C_D_wire(v_local, D, rho, eta);
		integral_sum += C_D_local*p*p*dp;
	}
	double a_D_wire = 0.5*rho*omega*omega*D*integral_sum/m; //wire's mass is negligible compared to the sphere's mass
	if (v > 0) {
		a_D_wire = -a_D_wire;
	}
	return a_D_wire;
}