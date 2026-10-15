#pragma once
#include <cmath>
//assuming good practice (Re <= 1)

inline double Calculate_a_D_sphere_Stokes(const double v, const double r, const double m) {
	const double eta = 1.81e-5; //air viscosity (at 20°C)
	double a_D = -6*M_PI*eta*r*v/m;
	return a_D;
}