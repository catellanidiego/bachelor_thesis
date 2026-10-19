#pragma once
#include <cmath>
//assuming good practice (Re <= 1)

inline double Calculate_a_D_sphere_Stokes(double v, double r, double m, const double eta) {
	double a_D = -6*M_PI*eta*r*v/m;
	return a_D;
}