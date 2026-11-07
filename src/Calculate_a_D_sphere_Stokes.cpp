#include <cmath>
#include <numbers>
#include "Calculate_a_D_sphere_Stokes.hpp"
//assuming good practice (Re <= 1)

double Calculate_a_D_sphere_Stokes(double v, double r, double m, double eta) {
	double a_D = -6*std::numbers::pi*eta*r*v/m;
	return a_D;
}