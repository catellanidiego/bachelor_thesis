#pragma once
#include <vector>
#include <Eigen/Dense>
struct solution_type {
	std::vector<double> timestamps;
	std::vector<Eigen::VectorXd> variables;
};