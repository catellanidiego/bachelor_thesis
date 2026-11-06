#include <cmath>
#include "Calculate_a_D_sphere_no_Stokes"
//assuming good practice (Re > 1)

double Calculate_a_D_sphere_no_Stokes (double v, double C_D, double Area, double m, double rho) {
	double a_D = -0.5*(rho/m)*C_D*Area*v*std::abs(v);
	return a_D;
}