#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <functional>
//#include "include/RK45_Solver.hpp"
#include "include/CycloidalPendulum.hpp"
#include "include/Solution_type.hpp"
#include "include/Calculate_K.hpp"
#include "include/Calculate_U.hpp"
#include "include/Calculate_Re.hpp"
#include "include/Calculate_a_D_Stokes.hpp"
#include "include/Calculate_a_D_White.hpp"
//PARAMETRI DI RK45: funzione, t_finale, stato iniziale, delta_t, atol, rtol, h_new_max
const double g_prova = 9.81;
struct F_1 {
	double R_F;
	double r_F;
	double m_F;
	F_1(double R_int, double r_int, double m_int) : R_F(R_int), r_F(r_int), m_F(m_int) {} 
	Eigen::VectorXd operator()(double t, const Eigen::Vector2d& Y) const {
		Eigen::Vector2d res;
		res(0) = Y(1);
		double Re = Calculate_Re(Y(1), r_F);
		if (Re <= 1) {
			double a_D = Calculate_a_D_Stokes(Y(0), Y(1), m_F);
			res(1) = -g_prova/(4*R_F)*Y(0) + a_D;
		}
		else if (Re > 1 && Re <= 2e5) {
			double A = M_PI*std::pow(2,Y(0));
			double a_D = Calculate_a_D_White(Y(1), r_F, A, m_F);
			res(1) = -g_prova/(4*R_F)*Y(0) + a_D;
		}
		return res;
	}
};

int main() {
	double r = 0.01;
	double R = 0.08;
	double m = 0.08;
	double s = 0.3;
	double v = 0.0;
	CycloidalPendulum C(r, R, m, s, v);
	double r_tol = 1e-6;
	double a_tol = 1e-6;
	double delta_t = 1e-6;
	double T = C.calculate_T();
	double h_new_max = T/100; //get at least 100 points
	Eigen::Vector2d Y;
	Y(0) = 0.3;
	Y(1) = 0.0;
	F_1 my_F(R, r, m);
	solution_type S = RK_45<F_1>(my_F, 10.0, Y, delta_t, a_tol, r_tol, h_new_max);
	return 0;
}
