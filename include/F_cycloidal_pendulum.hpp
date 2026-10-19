#pragma once
#include <Eigen/Dense>
#include "Calculate_a_D_sphere_Stokes.hpp"
#include "Calculate_a_D_sphere_no_Stokes.hpp"
#include "Calculate_C_D_sphere_White.hpp"
#include "Calculate_a_friction.hpp"
#include "Calculate_Re.hpp"
#include "Calculate_a_D_wire.hpp"
#include "Parameters.hpp"

class F {
	double r_F;
	double R_F;
	double m_F;
	double mu_eq_F;
	double D_F;
	double g;
	double rho;
	double eta;
	double epsilon;
	public:	
		F(double r_int, double R_int, double m_int, double mu_eq_int, double D_int, double g_int, double rho_int, double eta_int, double epsilon_int) : r_F(r_int), R_F(R_int), m_F(m_int), mu_eq_F(mu_eq_int), D_F(D_int), g(g_int), rho(rho_int), eta(eta_int), epsilon(epsilon_int) {} 
		Eigen::VectorXd operator()(double t, const Eigen::Vector2d& Y) const {
			Eigen::Vector2d res;
			res(0) = Y(1);
			res(1) = Calculate_a_friction(mu_eq_F, Y(1), Y(0), R_F, epsilon, g);
			double Re_sphere = Calculate_Re(Y(1), r_F, rho, eta);
			if (Re_sphere <= 1) {
				double a_D_sphere = Calculate_a_D_sphere_Stokes(Y(1), r_F, m_F, eta);
				res(1) += -g/(4*R_F)*Y(0) + a_D_sphere + t*0; //avoid unusued variables warning
			}
			else {
				double C_D;
				if (Re_sphere > 1 && Re_sphere <= 2e5) {C_D = Calculate_C_D_sphere_White(Y(1), r_F, rho, eta);}
				else {C_D = 0.1;}  //Case Re>2e5
				
				double Area = M_PI*r_F*r_F;
				double a_D_sphere = Calculate_a_D_sphere_no_Stokes(Y(1), C_D, Area, m_F, rho);
				res(1) += -g/(4*R_F)*Y(0) + a_D_sphere;
			}

			double a_D_wire = Calculate_a_D_wire(R_F, Y(0), Y(1), D_F, m_F, rho, eta);
			res(1) += a_D_wire;
			return res;
	}
};
