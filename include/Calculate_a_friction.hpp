#pragma once
#include <cmath>

inline double Calculate_a_friction(const double mu_eq, const double v, const double s, const double R, const double epsilon, const double g) {
	double rad_arg = std::max(0.0, 16*R*R-s*s); //avoid complex numbers
	double P = std::sqrt(rad_arg);
	if (P < 1e-6) {P = 1e-6;} //avoid dividing by zero.
	double a_friction = -mu_eq*(2.0/M_PI)*std::atan(v/epsilon)*(g*P/(4.0*R) + v*v/P);
	return a_friction;
}