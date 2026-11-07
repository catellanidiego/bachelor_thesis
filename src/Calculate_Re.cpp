#include <cmath>
#include "Calculate_Re.hpp"

double Calculate_Re(double v, double r, double rho, double eta) {
	double Re = 2*r*rho*std::abs(v)/eta; 
	return Re;
}