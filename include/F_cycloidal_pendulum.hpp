#pragma once
#include <Eigen/Dense>
#include "Calculate_a_D_sphere_Stokes.hpp"
#include "Calculate_a_D_sphere_no_Stokes.hpp"
#include "Calculate_C_D_sphere_White.hpp"
#include "Calculate_a_Coulomb.hpp"
#include "Calculate_Re.hpp"
#include "Calculate_a_D_wire.hpp"

class F {
	const double g = 9.81;
	double r_F;
	double R_F;
	double m_F;
	double mu_d_F;
	double D_F;
	public:	
		F(double r_int, double R_int, double m_int, double mu_d_int, double D_int) : r_F(r_int), R_F(R_int), m_F(m_int), mu_d_F(mu_d_int), D_F(D_int) {} 
		Eigen::VectorXd operator()(double t, const Eigen::Vector2d& Y) const {
			Eigen::Vector2d res;
			res(0) = Y(1);
			res(1) = Calculate_a_Coulomb(mu_d_F, Y(1), Y(0), R_F);
			double Re_sphere = Calculate_Re(Y(1), r_F);
			if (Re_sphere <= 1) {
				double a_D_sphere = Calculate_a_D_sphere_Stokes(Y(1), r_F, m_F);
				res(1) += -g/(4*R_F)*Y(0) + a_D_sphere + t*0; //avoid unusued variables warning
			}
			else {
				double C_D;
				if (Re_sphere > 1 && Re_sphere <= 2e5) {C_D = Calculate_C_D_sphere_White(Y(1), r_F);}
				else {C_D = 0.1;}  //Case Re>2e5
				
				double Area = M_PI*r_F*r_F;
				double a_D_sphere = Calculate_a_D_sphere_no_Stokes(Y(1), C_D, Area, m_F);
				res(1) += -g/(4*R_F)*Y(0) + a_D_sphere;
			}

			double a_D_wire = Calculate_a_D_wire(R_F, Y(0), Y(1), D_F, m_F);
			res(1) += a_D_wire;
			return res;
	}
};