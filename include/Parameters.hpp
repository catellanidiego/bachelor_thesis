#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
struct Parameters {
        double R;
        double r;
        double m;
        double s;
        double v;
        double a_tol;
        double r_tol;
        double delta_t;
        int n_periods;
        double h_new_min;
	double D;
        double mu_eq;
	double epsilon;
	double E_tol;
	double mu_tol;
	double s_i;
	int n_periods_mu;
	double E_final;
	double g;
	double rho;
	double eta;
	double T_final_mu;
	double theta_tol;

	Parameters() { //default constructor
	        R = 0.08;
                r = 0.01187;
                m = 0.08;
                s = 0.3;
                v = 0.0;
                a_tol = 1e-10;
                r_tol = 1e-10;
                delta_t = 1e-3;
                n_periods = 10;
                h_new_min = 1e-12;
                D = 0.00028;
                mu_eq = 0.00017;
		epsilon = 1e-6;
		E_tol = 1e-10;
		mu_tol = 1e-10;
		s_i = 0.137607;
		n_periods_mu = 134;
		E_final = 0.00996774;
		g = 9.81;
		rho = 1.204;
		eta = 1.81e-5;
		T_final_mu = 158.55;
		theta_tol = 1e-6;
	}
	
	void validate() const {
		if (R <= 0) throw std::invalid_argument("Error: the generator ray must be > 0");
		if (r <= 0) throw std::invalid_argument("Error: the sphere's ray must be > 0");
		if (m <= 0) throw std::invalid_argument("Error: the sphere's mass must be > 0");
		if (std::abs(s) > 4*R) throw std::invalid_argument("Error: the sphere's initial position must be <= 4R");
		if (a_tol <= 0) throw std::invalid_argument("Error: the absolute tolerance must be > 0");
		if (r_tol <= 0) throw std::invalid_argument("Error: the relative tolerance must be > 0");
		if (delta_t <= 0) throw std::invalid_argument("Error: the time step must be > 0");
		if (n_periods < 0) throw std::invalid_argument("Error: the number of periods must be >= 0");
		if (h_new_min < 0) throw std::invalid_argument("Error: the new minimum step must be >= 0");
		if (D < 0) throw std::invalid_argument("Error: the wire diameter must be >= 0");
		if (mu_eq < 0) throw std::invalid_argument("Error: the mu_eq coefficient must be >= 0");
		if (epsilon <= 0) throw std::invalid_argument("Error: the epsilon must be > 0");
		if (E_tol <= 0) throw std::invalid_argument("Error: the epsilon must be > 0");
		if (mu_tol <= 0) throw std::invalid_argument("Error: the epsilon must be > 0");
		if (std::abs(s_i) > 4*R) throw std::invalid_argument("Error: the initial position for mu_ed data extraction must be < 4*R");
		if (n_periods_mu < 0) throw std::invalid_argument("Error: the number of periods for mu_ed data extraction must be >= 0");
		if (E_final < 0) throw std::invalid_argument("Error: the finale energy must be >= 0");
		if (rho <= 0) throw std::invalid_argument("Error: the air density (rho) must be > 0");
		if (eta <= 0) throw std::invalid_argument("Error: the air viscosity (eta) must be > 0");
		if (T_final_mu <= 0) throw std::invalid_argument("Error: the final time for mu calculation must be > 0");
		if (theta_tol <= 0) throw std::invalid_argument("Error: the tolerance for theta must be > 0");
	
	}
};
