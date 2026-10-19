#pragma once

inline double Calculate_U(const double h, const double m, const double g) { //potential energy
	double U = g * m * h;
	return U;
}