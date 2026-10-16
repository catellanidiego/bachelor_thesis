#include <iostream>
#include <Eigen/Dense>
#include <cctype>
#include <limits>
#include "CycloidalPendulum.hpp"
#include "RK45_Solver.hpp"
#include "F_cycloidal_pendulum.hpp"
#include "CSV_Writer.hpp"
#include "Timecounter.h"

int main() {	
	double R;
	double r;
	double m;
	double s;
	double v;
	double a_tol;
	double r_tol;
	double delta_t;
	double n_periods;
	double h_new_min;
	double mu_eq;
	double D;

	double manual_insert;
	std::cout << "Do you wish to insert values manually or use the default ones?" << "\n"
		  << "   Default cycloid's generator ray = 0.08 meters" << "\n"
		  << "   Default sphere's ray = 0.01 meters" << "\n"
		  << "   Default sphere's mass = 0.08 kg " << "\n"
		  << "   Default initial position = 0.3 meters" << "\n"
		  << "   Default initial velocity = 0.0 m/s" << "\n" 
		  << "   Default absolute tolerance = 1e-12" << "\n"
		  << "   Default relative tolearnce = 1e-12" << "\n"
		  << "   Default first delta t = 1e-3" << "\n"
		  << "   Default n° of periods = 10" << "\n"
		  << "   Default minimum for new delta t = 1e-12" << "\n"
		  << "   Default wire diameter = 0.00028" << "\n"
		  << "   Default mu_eq = 0.000244141" << "\n"
	          << "Press 1 for default values." << "\n" 
		  << "Press 2 for manual insertion." << std::endl;
	while (!(std::cin >> manual_insert) || (manual_insert != 1 && manual_insert != 2)) {
		std::cout << "Invalid input, press 1 for default values, press 2 for manual insertion" << std::endl;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
 	}

	if (manual_insert == 1) {
		R = 0.08;
		r = 0.01;
		m = 0.08;
		s = 0.3;
		v = 0.0;
		a_tol = 1e-12; 
		r_tol = 1e-12;
		delta_t = 1e-3;
		n_periods = 10;
		h_new_min = 1e-12;
		D = 0.00028;
		mu_eq = 0.000244141;
	}
	
	else {
		std::cout << "Enter cycloid's generator ray (meters): " << std::endl;
		while (!(std::cin >> R) || R <= 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, R must be > 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//tutti così e endl;

		std::cout << "Enter sphere's ray (meters): " << std::endl;
		while (!(std::cin >> r) || r <= 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, r must be > 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
		std::cout << "Enter sphere's mass (kg): " << std::endl;
		while (!(std::cin >> m) || m <= 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, m must be > 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
		std::cout << "Enter sphere's position (curviliear abscissa) (meters): " << std::endl;
		while (!(std::cin >> s) || s < 0 || s > 4*R) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, s must be >= 0 and <=4*R. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
		std::cout << "Enter sphere's velocity (m/s): " << std::endl;
		while (!(std::cin >> v)) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, R must be a number. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');;
		
			
		std::cout << "Enter absolute tolerance: " << std::endl;
		while (!(std::cin >> a_tol) || a_tol <= 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, a_tol must be > 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cout << "Enter relative tolerance: " << std::endl;
		while (!(std::cin >> r_tol) || r_tol <= 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, r_tol must be > 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


		std::cout << "Enter first delta t: " << std::endl;
		while (!(std::cin >> delta_t) || delta_t <= 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, delta_t must be > 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		

		std::cout << "Enter number of periods: " << std::endl;
		while (!(std::cin >> n_periods) || n_periods <= 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, the number of periods must be > 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		
		std::cout << "Enter minimum for new delta t: " << std::endl;
		while (!(std::cin >> h_new_min) || h_new_min <= 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, minimum for new delta t must be > 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		

		std::cout << "Enter wire diameter: " << std::endl;
		while (!(std::cin >> D) || D <= 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, wire diameter must be > 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		
		std::cout << "Enter mu_eq coefficient: " << std::endl;
		while(!(std::cin >> mu_eq) || mu_eq < 0) {
			if (std::cin.fail()) {
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, mu_eq must be >= 0. Try again: " << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		

	} //END OF ELSE

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
	CycloidalPendulum C(r, R, m);
	if (toupper(time_count) == 'Y') {
		timecounter tc;
		tc.tic();
		Eigen::Vector2d Y = {s, v};
		F my_F(r, R, m, mu_eq, D);
		double T = C.calculate_T();
		double h_new_max = T/100; //get at least 100 points per period
		double total_T = T*n_periods;
		S = RK_45<F>(my_F, total_T, Y, delta_t, a_tol, r_tol, h_new_min, h_new_max);
		double secs = tc.toc();
		std::cout << "Elapsed time = " << secs << " seconds" << std::endl;
	}
	
	else {
		Eigen::Vector2d Y = {s, v};
		F my_F(r, R, m, mu_eq, D);
		double T = C.calculate_T();
		double h_new_max = T/100; //get at least 100 points
		double total_T = T*n_periods;
		S = RK_45<F>(my_F, total_T, Y, delta_t, a_tol, r_tol, h_new_min, h_new_max);
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
	
	print(S.timestamps, x_vec, y_vec, v_vec, theta_vec, omega_vec, m); 
	
	return 0;
}
