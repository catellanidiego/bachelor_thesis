#pragma once
#include "Calculate_p_f.hpp"

inline double Calculate_a_friction(double mu_eq, double v, double s, double R, double epsilon, double g) {
	double p_f = Calculate_p_f(R, s);
	if (P < 1e-6) {P = 1e-6;} //avoid dividing by zero.
	double a_friction = -mu_eq*(2.0/M_PI)*std::atan(v/epsilon)*(g*P/(4.0*R) + v*v/P);
	return a_friction;
}