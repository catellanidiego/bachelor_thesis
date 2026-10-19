#pragma once
#include <vector>
#include <fstream>
#include "Calculate_U.hpp"
#include "Calculate_K.hpp"

void print (const std::vector<double>& t_vec, const std::vector<double>& x_vec, const std::vector<double>& y_vec, const std::vector<double>& v_vec, const std::vector<double>& theta_vec, const std::vector<double>& omega_vec ,const double m, double g) {
	std::ofstream x_y_file;
	std::ofstream t_x_y_file;
	std::ofstream theta_omega_file;
	std::ofstream t_E_file;
	
	x_y_file.open("../csv/CSV_x_y.csv");
	t_x_y_file.open("../csv/CSV_t_x_y.csv");
	theta_omega_file.open("../csv/CSV_theta_omega.csv");
	t_E_file.open("../csv/CSV_E.csv");

	for (size_t i = 0; i < t_vec.size(); i++) { //all vectors have the same size
		double t = t_vec[i];
		double x = x_vec[i];
		double y = y_vec[i];
		double v = v_vec[i];
		double theta = theta_vec[i];
		double omega = omega_vec[i];
		double K = Calculate_K(v, m);
		double U = Calculate_U(y, m, g);
		double E = K + U;
		x_y_file << x << ", " << y << "\n";
		t_x_y_file << t << ", " << x << ", " << y << "\n";
		theta_omega_file << theta << ", " << omega << "\n";
		t_E_file << t << ", " << E << "\n";
	}
	x_y_file.close();
	t_x_y_file.close();
	theta_omega_file.close();
	t_E_file.close();
}