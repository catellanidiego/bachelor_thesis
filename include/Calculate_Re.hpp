#pragma once
#include <cmath>

double Calculate_Re(const double v, const double r) {
	const double rho = 1.204; //air density  (at 20 °C and sea level)
	const double eta = 1.81e-5; //air viscosity (at 20°C)
	double Re = 2*r*rho*std::abs(v)/eta; 
	return Re;
}