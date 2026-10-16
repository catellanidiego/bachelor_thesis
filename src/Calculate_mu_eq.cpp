#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include "CycloidalPendulum.hpp"
#include "RK45_Solver.hpp"
#include "F_cycloidal_pendulum.hpp"
#include "Calculate_K.hpp"
#include "Calculate_U.hpp"

//MANCANO s e E_ref
int main() {
	const double E_ref = 0.0217468; //calculated
	const double epsilon = 1e-6;
	
	double mu_low = 0.0;
	double mu_high = 0.05; //upper bound
	double mu_eq = (mu_high + mu_low) / 2.0;
	double R = 0.08;
	double r = 0.01;
	double m = 0.08;
	double s = 0.137567; //calculated
	double v = 0.0;
	double D = 2.8e-4;
	double a_tol = 1e-6;
	double r_tol = 1e-6;
	double delta_t = 1e-3;
	double n_periods = 100; //cambia
	double h_new_min = 1e-12;
	CycloidalPendulum C(r, R, m);
	Eigen::Vector2d Y = {s, v};
	double T = C.calculate_T();
	double h_new_max = T/100;
	double total_T = T*n_periods;
	while (1) {
		F my_F(r, R, m, mu_eq, D);
		solution_type S = RK_45<F>(my_F, total_T, Y, delta_t, a_tol, r_tol, h_new_min, h_new_max);
		Eigen::Vector2d Y_last = S.variables.back();
		double s_int = Y_last(0);
		double v_int = Y_last(1);
		double y_int = C.y_from_s(s_int);
		double K = Calculate_K(v_int, m);
		double U = Calculate_U(y_int, m);
		double E = K + U;
		if (std::abs(E - E_ref) < epsilon) {
			break;
		}
		if ((mu_high - mu_low) < epsilon) {
			std::cout << "Maximum precision for mu_eq reached." << std::endl;
			break;
		}
		else {
			if (E > E_ref) {
				mu_low = mu_eq
;
			}
			else if (E < E_ref) {
				mu_high = mu_eq;
			}
			mu_eq = (mu_high + mu_low) / 2.0;
		}
	} 
	std::cout << "The value of mu_eq is " << mu_eq << std::endl;
	return 0;
}