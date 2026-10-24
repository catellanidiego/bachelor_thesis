#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include "CSV_Reader.hpp"
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
	
	std::string f_dir;
	std::cout << "Insert csv file directory" << std::endl;
	while (!(std::cin >> f_dir)) {
		if (std::cin.fail()) {
			std::cin.clear();
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again" << std::endl;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::vector<std::vector<double>> V = CSV_reader<double>(f_dir, 2);
	std::vector<double> t_vec = V[0];
	std::vector<double> x_vec = V[1];
	std::vector<double> crossings;
	for (size_t i = 0; i < x_vec.size() - 1; i++) {
		if (x_vec[i]* x_vec[i+1] < 0.0) {
			double j = (x_vec[i+1] - x_vec[i])/ (t_vec[i+1] - t_vec[i]);
			double t_zero = t_vec[i] - (x_vec[i]/j);
			crossings.push_back(t_zero);
		}
	}
	
	if (crossings.size() >= 3) {
		double period = crossings[2] - crossings[0];
		double x_max = 0.0;
		double x_min = 0.0;
		for (size_t i = 0; i < t_vec.size(); i++) {
			if (t_vec[i] >= crossings[0] && t_vec[i] <= crossings[2]) {
 				double x = x_vec[i];
				if (x > x_max) {x_max = x;}
				if (x < x_min) {x_min = x;}
			}
		}
		double amplitude = 0.5*(x_max-x_min);
		double theta_s = std::asin(amplitude/(4.0*p.R));
		double theta_c_low = 0.0;
		double theta_c_high = M_PI/2.0;
		double theta_c = (theta_c_low + theta_c_high)/2.0;
		double amplitude_c = 0.0;
		while ((theta_c_high - theta_c_low) > p.theta_tol) {
			amplitude_c = p.R*(2.0*theta_c + std::sin(2.0*theta_c));
			if (amplitude_c < amplitude) {theta_c_low = theta_c;}
			else if (amplitude_c > amplitude) {theta_c_high = theta_c;}
			theta_c = (theta_c_low + theta_c_high)/2.0;
		}
		std::cout << "Period = " << period << " s" << std::endl;
		std::cout << "Amplitude = " << amplitude << std::endl;
		std::cout << "Theta for standard pendulum = " << theta_s << std::endl;
		std::cout << "Theta for cycloidal pendulum = " << theta_c << std::endl;
	}
	else {std::cout << "Not enough data to calculate T" << std::endl;}

	return 0;
}
