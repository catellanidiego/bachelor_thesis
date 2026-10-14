#pragma once
#include "Solution_type.hpp"
#include <vector>
#include <Eigen/Dense>
#include <cmath>

const std::vector<double> A = {0, 1.0/4.0, 3.0/8.0, 12.0/13.0, 1.0, 1.0/2.0};
const std::vector<double> B_1 = {2.0/9.0}; //corrisponde a k_1
const std::vector<double> B_2 = {1.0/12.0, 1.0/4.0};
const std::vector<double> B_3 = {69.0/128.0, -243.0/128.0, 135.0/64.0};
const std::vector<double> B_4 = {-17.0/12.0, 27.0/4.0, -27.0/5.0, 16.0/15.0};
const std::vector<double> B_5 = {65.0/432.0, -5.0/16.0, 13.0/16.0, 4.0/27.0, 5.0/144.0};
const std::vector<double> C_4 = {1.0/9.0, 0, 9.0/20.0, 16.0/45.0, 1.0/12.0, 0};
const std::vector<double> C_5 = {47.0/450.0, 0, 12.0/25.0, 32.0/225.0, 1.0/30.0, 6.0/25.0};

template <typename Function>
solution_type RK_45(const Function& F, double t_final, Eigen::VectorXd Y, double h, double a_tol, double r_tol, double h_new_max) { 
	double t = 0.0;
	solution_type S;
	S.timestamps.push_back(t);
	S.variables.push_back(Y);
	while (t < t_final) {
		if (t + h > t_final) {
			h = t_final - t; //manage the final timestamp
		}
		while (1) {
			Eigen::VectorXd F_k_1 = F(t, Y);
			Eigen::VectorXd k_1 = h*F_k_1;

			Eigen::VectorXd F_k_2 = F(t + A[1]*h, Y + B_1[0]*k_1);
			Eigen::VectorXd k_2 = h*F_k_2;

			Eigen::VectorXd F_k_3 = F(t + A[2]*h, Y + B_2[0]*k_1 + B_2[1]*k_2);
			Eigen::VectorXd k_3 = h*F_k_3;

			Eigen::VectorXd F_k_4 = F(t + A[3]*h, Y + B_3[0]*k_1 + B_3[1]*k_2 + B_3[2]*k_3);
			Eigen::VectorXd k_4 = h*F_k_4;
			
			Eigen::VectorXd F_k_5 = F(t + A[4]*h, Y + B_4[0]*k_1 + B_4[1]*k_2 + B_4[2]*k_3 + B_4[3]*k_4);
			Eigen::VectorXd k_5 = h*F_k_5;

			Eigen::VectorXd F_k_6 = F(t + A[5]*h, Y + B_5[0]*k_1 + B_5[1]*k_2 + B_5[2]*k_3 + B_5[3]*k_4 + B_5[4]*k_5);
			Eigen::VectorXd k_6 = h*F_k_6;	
			
			Eigen::VectorXd TE = ( (C_5[0]-C_4[0])*k_1 + (C_5[1]-C_4[1])*k_2 + (C_5[2]-C_4[2])*k_3 + (C_5[3]-C_4[3])*k_4 + (C_5[4]-C_4[4])*k_5 + (C_5[5]-C_4[5])*k_6).cwiseAbs();
			Eigen::VectorXd epsilon = a_tol*Eigen::VectorXd::Ones(Y.size()) + r_tol*Y.cwiseAbs();
			Eigen::VectorXd error_rapports = TE.cwiseQuotient(epsilon);
			double worst_error = error_rapports.maxCoeff();
			if (worst_error < 1e-15) {
				worst_error = 1e-15; //avoid dividing by zero
			}

			double h_new = 0.9*h*std::pow(1.0/worst_error, 0.2);
			if (h_new > h_new_max) {
				h_new = h_new_max;
			};
			
			if (h_new < a_tol) {
				h_new = a_tol;
			};
			
			if (worst_error <= 1.0) {
				t = t + h;
				Y = Y + C_5[0]*k_1 + C_5[1]*k_2 + C_5[2]*k_3 + C_5[3]*k_4 + C_5[4]*k_5 + C_5[5]*k_6;
				S.timestamps.push_back(t);
				S.variables.push_back(Y);
				h = h_new;
				break;
			}
			h = h_new;
		} //internal while loop
	} //external while loop
	return S;
};
