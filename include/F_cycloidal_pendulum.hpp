#pragma once
#include <Eigen/Dense>
#include "Calculate_a_D_Stokes.hpp"
#include "Calculate_a_D_White.hpp"
#include "Calculate_a_Coulomb.hpp"
#include "Calculate_Re.hpp"

class F {
	const double g = 9.81;
	double r_F;
	double R_F;
	double m_F;
	double mu_d_F;
	public:	
		F(double r_int, double R_int, double m_int, double mu_d_int) : r_F(r_int), R_F(R_int), m_F(m_int), mu_d_F(mu_d_int) {} 
		Eigen::VectorXd operator()(double t, const Eigen::Vector2d& Y) const {
			Eigen::Vector2d res;
			res(0) = Y(1);
			res(1) = Calculate_a_Coulomb(mu_d_F, Y(1), Y(0), R_F);
			double Re = Calculate_Re(Y(1), r_F);
			if (Re <= 1) {
				double a_D = Calculate_a_D_Stokes(Y(1), r_F, m_F);
				res(1) += -g/(4*R_F)*Y(0) + a_D + t*0; //avoid unusued variables warning
			}
			else if (Re > 1 && Re <= 2e5) {
				double Area = M_PI*r_F*r_F;
				double a_D = Calculate_a_D_White(Y(1), r_F, Area, m_F);
				res(1) += -g/(4*R_F)*Y(0) + a_D;
			}
			return res;
	}
};