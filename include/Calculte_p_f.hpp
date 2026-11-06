#pragma once
#include <cmath>

inline double Calculate_p_f(double R, double s) {
	double p_f = std::sqrt(std::max(0.0, 16*R*R-s*s)); //avoid complex numbers
	return p_f;

}