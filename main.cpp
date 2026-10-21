#include <iostream>
#include <Eigen/Dense>
#include <cctype>
#include <limits>
#include <stdexcept>
#include "CycloidalPendulum.hpp"
#include "RK45_Solver.hpp"
#include "F_cycloidal_pendulum.hpp"
#include "CSV_Writer.hpp"
#include "Timecounter.h"
#include "Parameters.hpp"
#include "Load_config.hpp"

int main() {	
	Parameters p;
	load_config("../config.txt", p);
	try { 
		p.validate();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	char time_count;
	std::cout << "Do you wish record the algorithm speed? (y/n)" << std::endl;
	while (!(std::cin >> time_count) || (toupper(static_cast<unsigned char>(time_count)) != 'Y' && toupper(static_cast<unsigned char>(time_count)) != 'N')) {
		if (std::cin.fail()) {
			std::cin.clear();
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input: press (y/n)" << std::endl;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	solution_type S;
	CycloidalPendulum C(p.r, p.R, p.m);
	if (toupper(time_count) == 'Y') {
		try {
			timecounter tc;
			tc.tic();
			Eigen::Vector2d Y = {p.s, p.v};
			F my_F(p.r, p.R, p.m, p.mu_eq, p.D, p.g, p.rho, p.eta, p.epsilon);
			double T = C.calculate_T();
			double h_new_max = T/100; //get at least 100 points per period
			double total_T = T*p.n_periods;
			S = RK_45<F>(my_F, total_T, Y, p.delta_t, p.a_tol, p.r_tol, p.h_new_min, h_new_max);
			double secs = tc.toc();
			std::cout << "Elapsed time = " << secs << " seconds" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
	
	else {
		try {
			Eigen::Vector2d Y = {p.s, p.v};
			F my_F(p.r, p.R, p.m, p.mu_eq, p.D, p.g, p.rho, p.eta, p.epsilon);
			double T = C.calculate_T();
			double h_new_max = T/100; //get at least 100 points
			double total_T = T*p.n_periods;
			S = RK_45<F>(my_F, total_T, Y, p.delta_t, p.a_tol, p.r_tol, p.h_new_min, h_new_max);
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
	std::vector<double> x_vec;
	std::vector<double> y_vec;
	std::vector<double> v_vec;
	std::vector<double> theta_vec;
	std::vector<double> omega_vec;
	for (const Eigen::VectorXd& W : S.variables) {
		double s_int = W(0);
		double x_s = C.x_from_s(s_int);
		double y_s = C.y_from_s(s_int);
		double vel = W(1);
		double theta = C.theta_from_s(s_int);
		double omega = C.omega_from_v_s(vel,s_int);
		x_vec.push_back(x_s);
		y_vec.push_back(y_s);
		v_vec.push_back(vel);
		theta_vec.push_back(theta);
		omega_vec.push_back(omega);
	}
	
	print(S.timestamps, x_vec, y_vec, v_vec, theta_vec, omega_vec, p.m, p.g); 
	
	return 0;
}
