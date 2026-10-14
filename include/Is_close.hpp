#pragma once
#include <cmath>
#include <algorithm>

inline bool is_close(double a, double b, double r_tol, double a_tol) {
	if (a == b) {
		return true;
	}
	double diff = std::abs(a-b);
	if (diff <= a_tol) {
		return true;
	}
	bool res = diff <= r_tol*std::max(std::abs(a), std::abs(b)); 
	return res;
}