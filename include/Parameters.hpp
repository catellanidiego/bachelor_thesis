#pragma once
#include <fstream>
#include <string>
#include <iostream>
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
	double s_i;
	int n_periods_mu;
	double E_final;
	double g;
	double rho;
	double eta;

	Parameters() { //default constructor
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
                mu_eq = 0.000185242;
		epsilon = 1e-6;
		s_i = 0.137607;
		n_periods_mu = 144;
		E_final = 0.00996774;
		g = 9.81;
		rho = 1.204;
		eta = 1.81e-5;
	}
};
