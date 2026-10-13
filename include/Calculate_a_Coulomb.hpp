#pragma once
#include <cmath>
double Calculate_a_Coulomb(const double mu_d, const double v, const double s, const double R) {
	const double g = 9.81;
	const double epsilon = 1e-6;
	double rad_arg = std::max(0.0, 16*R*R-s*s); //avoid complex numbers
	double rho = std::sqrt(rad_arg);
	if (rho < 1e-6) {rho = 1e-6;} //avoid dividing by zero.
	double a_Coulomb = -mu_d*(2.0/M_PI)*std::atan(v/epsilon)*(g*rho/(4.0*R) + v*v/rho);
	return a_Coulomb;
}