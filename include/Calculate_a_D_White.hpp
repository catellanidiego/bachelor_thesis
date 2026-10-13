#pragma once
#include <cmath>
#include "Calculate_C_D_White.hpp"
//assuming good practice (1 < Re <= 2*e5)

double Calculate_a_D_White (const double v, const double r, const double Area, const double m) {
	const double rho = 1.204; //air density  (at 20 °C and sea level)
	double C_D = Calculate_C_D_White(v, r);
	double a_D = -0.5*(rho/m)*C_D*Area*v*std::abs(v);
	return a_D;
}