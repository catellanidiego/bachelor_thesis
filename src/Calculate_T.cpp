#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <fstream>
#include "CSV_Reader.hpp"
#include "Parameters.hpp"
#include "Load_config.hpp"

int main() {
	Parameters p;
	load_config("../config.txt", p);
	try { 
		p.validate();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	std::string f_dir;
	std::cout << "Insert csv file directory" << std::endl;
	while (!(std::cin >> f_dir)) {
		if (std::cin.fail()) {
			std::cin.clear();
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again" << std::endl;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::vector<std::vector<double>> V = CSV_reader<double>(f_dir, 2);
	std::vector<double> t_vec = V[0];
	std::vector<double> x_vec = V[1];
	std::vector<double> y_vec = V[2];

	const double prominence_threshold = 0.001;
	double sum_y = 0.0;
	for (const double y : y_vec) {
		sum_y = sum_y + y;}
	double y_avg = sum_y/y_vec.size();
	std::vector<double> inversions;
	double current_max_y = -std::numeric_limits<double>::infinity();
	int current_max_index = -1;
	bool peak_found = 0;
	for (size_t i=0; i < y_vec.size(); i++) {
		if (peak_found == 0) {
			if (y_vec[i] > y_avg) {
				if (y_vec[i] > current_max_y) {
					current_max_index = i;
					current_max_y = y_vec[i];
				}
				else if (y_vec[i] < current_max_y - prominence_threshold) {
					inversions.push_back(current_max_index);
					peak_found = 1;
				}
			}
		}
		else if (y_vec[i] < y_avg) {
			peak_found = 0;
			current_max_y = -std::numeric_limits<double>::infinity();
		}
	}
	if (inversions.size() >= 3) {
		int i_index = inversions[0];
		int f_index = inversions[2];
		double t_i = t_vec[i_index];
		double t_f = t_vec[f_index];
		double period = t_f - t_i;
		std::cout << "Period = " << period << " s" << std::endl; 
	}

	return 0;
}
