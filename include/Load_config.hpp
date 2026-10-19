#pragma once
void load_config(const std::string& filename, Parameters& p) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "File not found. Using default parameters" << std::endl;
	return;
	}
	std::string key;
	while (file >> key) {
		if (key == "R") {file >> p.R;}
		else if (key == "r") {file >> p.r;}
		else if (key == "m") {file >> p.m;}
		else if (key == "s") {file >> p.s;}
		else if (key == "v") {file >> p.v;}
		else if (key == "a_tol") {file >> p.a_tol;}
		else if (key == "r_tol") {file >> p.r_tol;}
		else if (key == "delta_t") {file >> p.delta_t;}
		else if (key == "n_periods") {file >> p.n_periods;}
		else if (key == "h_new_min") {file >> p.h_new_min;}
		else if (key == "D") {file >> p.D;}
		else if (key == "mu_eq") {file >> p.mu_eq;}
		else if (key == "epsilon") {file >> p.epsilon;}
		else if (key == "s_i") {file >> p.s_i;}
		else if (key == "n_periods_mu") {file >> p.n_periods_mu;}
		else if (key == "E_final") {file >> p.E_final;}
		else if (key == "g") {file >> p.g;}
		else if (key == "rho") {file >> p.rho;}
		else if (key == "eta") {file >> p.eta;}

	}
}
