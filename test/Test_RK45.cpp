#include "../include/solution_type.hpp"
#include "../include/RK45_Solver.hpp"
#include "../include/F_test.hpp"
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
int main() {
	int res = EXIT_SUCCESS;
	double delta_t = 1e-6;
	double a_tol = 1e-12;
	double r_tol = 1e-12;
	double s_0 = 1.0;
	double v_0 = 0.0;
	Eigen::Vector2d Y = {s_0, v_0};
	double omega = 2.0;
	double T = 2*M_PI/omega;
	double h_new_max = T/20; 
	F_test my_F(omega);
	solution_type S = RK_45<F_test>(my_F, T, Y, delta_t, a_tol, r_tol, h_new_max);
	int n = S.timestamps.size();
	Eigen::VectorXd exact_solution(n);
	Eigen::VectorXd numeric_solution(n);
	for (int i = 0; i < n; i++) {
		double t = S.timestamps[i];
		double s_exact = s_0*std::cos(omega*t);
		exact_solution(i) = s_exact;
		numeric_solution(i) = S.variables[i](0);
	}
	double max_error = (numeric_solution - exact_solution).lpNorm<Eigen::Infinity>();
	if (max_error > a_tol) {
		res = EXIT_FAILURE;
	}
	return res;
}
