#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <cmath>
#include "CSV_Reader.hpp"
#include "Parameters.hpp"
#include "Load_config.hpp"
//this program also creates the Data_for_comparison.csv file
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
	std::cout << "Insert csv file direcotry" << std::endl;
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
		sum_y += y;
	}
	double y_avg = sum_y/y_vec.size();
	std::vector<int> inversions;
	double current_max_y = - std::numeric_limits<double>::infinity();
	int current_max_index = -1;
	bool peak_found = 0;
	for (size_t i = 0; i < y_vec.size(); i++) {
		if (peak_found == 0) {
			if (y_vec[i] > y_avg) {
				if (y_vec[i] > current_max_y) {
					current_max_y = y_vec[i];
					current_max_index = i;
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
	
	if (inversions.size() > 0 && inversions.size() % 2 == 0) {
		inversions.pop_back();
	}
	
	if (inversions.size() > 0) {
		int first_inversion_index = inversions[0];
		int last_inversion_index = inversions[inversions.size() - 1];
		double y_first_inversion = y_vec[first_inversion_index];
		double y_last_inversion = y_vec[last_inversion_index];
		double s_1 = std::pow(8*p.R*y_first_inversion, 0.5);
		double initial_energy = p.m*p.g*y_first_inversion;
		double final_energy = p.m*p.g*y_last_inversion;
		double final_time = t_vec[last_inversion_index];
		int number_of_periods = ((inversions.size() - 1)/ 2);
		std::cout << "Number of periods = " << number_of_periods << std::endl;
		std::cout << "Initial curvilinear abscissa = " << s_1 << std::endl;
		std::cout << "Initial energy = " << initial_energy << std::endl;
		std::cout << "Final energy = " << final_energy << std::endl;
		std::cout << "Time of last period end" << final_time << std::endl; 
		std::string out_filename = "../csv/Data_for_comparison.csv";
		std::ofstream out_file(out_filename);
		if (out_file.is_open()) {
			for (size_t i = 0; i < inversions.size(); i++) {
				int index = inversions[i];
				out_file << t_vec[index] << ", " << y_vec[index] << "\n";
			}
			out_file.close();
			std::cout << "Data for comparison (t, y_inversion) written in the Data_for_comparison.csv file" << std::endl;
		}
	}

	return 0;
}
