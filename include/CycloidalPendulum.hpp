#pragma once
#include <cmath>
#include <Eigen/Dense>

class CycloidalPendulum {
	double r; //Sphere's ray (m)
	double R; //Cycloid's generator ray (m)
	double m; //Sphere's mass (kg)
	double s; //Sphere's position (m)
	double v; //Sphere's velocity (m/s)

	public:
		//default constructor
		CycloidalPendulum() {
		r = 0.0;
		R = 0.0;
		m = 0.0;
		}
	
	//user constructur
		CycloidalPendulum(double my_r, double my_R, double my_m) {
		//VERIFICHE DI COERENZA FISICA
			r = my_r;
			R = my_R;
			m = my_m;	
		}
		
		double x_from_s (const double s_int) const {
			double phi = std::asin(s_int/(4.0*R));
			double x_s = R*(2.0*phi + std::sin(2.0*phi));
			return x_s;
		}

		double y_from_s (const double s_int) const {
			double y_s = std::pow(s_int,2)/(8.0*R);
			return y_s;
		}

		double theta_from_s (const double s_int) const {	
			double theta = std::asin(s_int/(4.0*R));
			return theta;
		}

		double omega_from_v_s (const double v_int, const double s_int) const {
			double theta = theta_from_s(s_int);
			double omega = v_int/(4.0*R*std::cos(theta)); 
			return omega;
		}

		double calculate_T() const {
			const double g = 9.81;
			double T = 4*M_PI*std::pow(R/g,0.5);
			return T;
		}

};


