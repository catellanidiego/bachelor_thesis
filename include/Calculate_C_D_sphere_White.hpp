#pragma once
#include <cmath>
#include "Calculate_Re.hpp"

inline double Calculate_C_D_sphere_White(const double v, const double r, const double rho, const double eta) {
	double Re = Calculate_Re(v, r, rho, eta);
	double C_D = 24/Re + 6/(1+sqrt(Re)) + 0.4;
	return C_D;
}