#pragma once
#include <Eigen/Dense>

class F_test {
	double omega_F;
	public:
		F_test(double omega_int) : omega_F(omega_int) {}
		Eigen::VectorXd operator()([[maybe_unusued]] double t, const Eigen::VectorXd& Z) const {
			Eigen::VectorXd res;
			res(0) = Z(1); 
			res(1) = - omega_F*omega_F*Z(0);
			return res;
		}
};