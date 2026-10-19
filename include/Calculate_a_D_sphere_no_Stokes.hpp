#pragma once
#include <cmath>
//assuming good practice (Re > 1)

inline double Calculate_a_D_sphere_no_Stokes (const double v, const double C_D, const double Area, const double m, const double rho) {
	double a_D = -0.5*(rho/m)*C_D*Area*v*std::abs(v);
	return a_D;
}