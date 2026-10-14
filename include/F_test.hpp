#pragma once
#include <Eigen/Dense>

class F_test {
	double omega_F;
	public:
		F_test(double omega_int) : omega_F(omega_int) {}
		Eigen::Vector2d operator()(double t, const Eigen::Vector2d& Z) const {
			Eigen::Vector2d res;
			res(0) = Z(1) + t*0; //avoid unusue variable warning
			res(1) = - omega_F*omega_F*Z(0);
			return res;
		}
};