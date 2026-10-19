#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include "CycloidalPendulum.hpp"
#include "RK45_Solver.hpp"
#include "F_cycloidal_pendulum.hpp"
#include "Calculate_K.hpp"
#include "Calculate_U.hpp"
#include "Parameters.hpp"
#include "Load_config.hpp"

int main() {
	Parameters p;
	load_config("../config.txt", p);
	CycloidalPendulum C(p.r, p.R, p.m);
	double y_0 = C.y_from_s(p.s_i);
	double K_0 = Calculate_K(p.v, p.m);
	double U_0 = Calculate_U(y_0, p.m, p.g);
	double E_0 = K_0 + U_0;
	if (E_0 < p.E_final) {
		std::cerr << "Impossible to solve, initial energy is lower than final energy" << std::endl; 
		return 1;
	}
	double mu_low = 0.0;
	double mu_high = 0.01; //upper bound
	double mu_eq = (mu_high + mu_low) / 2.0;
	Eigen::Vector2d Y = {p.s_i, p.v};
	double T = C.calculate_T();
	double h_new_max = T/100;
	double total_T = T*p.n_periods_mu;
	while (1) {
		F my_F(p.r, p.R, p.m, mu_eq, p.D, p.g, p.rho, p.eta);
		solution_type S = RK_45<F>(my_F, total_T, Y, p.delta_t, p.a_tol, p.r_tol, p.h_new_min, h_new_max);
		Eigen::Vector2d Y_last = S.variables.back();
		double s_int = Y_last(0);
		double v_int = Y_last(1);
		double y_int = C.y_from_s(s_int);
		double K = Calculate_K(v_int, p.m);
		double U = Calculate_U(y_int, p.m, p.g);
		double E = K + U;
		if (std::abs(E - p.E_final) < p.epsilon) {
			break;
		}
		if ((mu_high - mu_low) < p.epsilon) {
			std::cout << "Maximum precision for mu_eq reached." << std::endl;
			break;
		}
		else {
			if (E > p.E_final) {
				mu_low = mu_eq
;
			}
			else if (E < p.E_final) {
				mu_high = mu_eq;
			}
			mu_eq = (mu_high + mu_low) / 2.0;
		}
	} 
	std::cout << "The value of mu_eq is " << mu_eq << std::endl;
	return 0;
}