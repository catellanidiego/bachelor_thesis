#pragma once
double Calculate_U(const double h, const double m) { //potential energy
	const double g = 9.81; //Gravity's acceleration
	double U = g * m * h;
	return U;
}