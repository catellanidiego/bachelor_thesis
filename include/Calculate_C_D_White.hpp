#pragma once
#include "Calculate_Re.hpp"
#include <cmath>
double Calculate_C_D_White(const double & v, const double& r) {
	double Re = Calculate_Re(v, r);
	double C_D = 24/Re + 6/(1+sqrt(Re)) + 0.4;
	return C_D;
}