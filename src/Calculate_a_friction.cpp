#include <cmath>
#include <numbers>
#include "Calculate_p_f.hpp"
#include "Calculate_a_friction.hpp"

double Calculate_a_friction(double mu_eq, double v, double s, double R, double epsilon, double g) {
	double p_f = Calculate_p_f(R, s);
	if (p_f < 1e-6) {p_f = 1e-6;} //avoid dividing by zero.
	double a_friction = -mu_eq*(2.0/std::numbers::pi)*std::atan(v/epsilon)*(g*p_f/(4.0*R) + v*v/p_f);
	return a_friction;
}