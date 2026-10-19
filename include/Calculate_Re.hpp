#pragma once
#include <cmath>

inline double Calculate_Re(const double v, const double r, const double rho, const double eta) {
	double Re = 2*r*rho*std::abs(v)/eta; 
	return Re;
}