#include <cmath>
#include <numbers>
#include "Calculate_Re.hpp"
#include "Calculate_C_D_wire.hpp"

double Calculate_C_D_wire(double v, double D, double rho, double eta) {
	double C_D_wire;
	double Re = Calculate_Re(v, D/2, rho, eta);
	if (Re < 1e-8) {Re = 1e-8;}
	if (Re <= 1e-4) {
		C_D_wire = (8*std::numbers::pi)/((Re)*(0.5-0.5772-std::log(Re/8))); 
	}
	else if (Re > 1e-4 && Re < 2e5) {
		C_D_wire = 1.18 + (6.8)/(std::pow(Re, 0.89)) + (1.96)/(std::sqrt(Re))- (0.0004*Re)/(1+3.64e-7*Re*Re);
	}
	else {
		C_D_wire = 0.3;
	}
	return C_D_wire;
}