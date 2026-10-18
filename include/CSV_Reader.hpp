#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
//assuming all data is of the same type
template <typename T>
inline std::vector<std::vector<T>> CSV_reader(const std::string& f_dir, int lines_to_skip) {
	std::vector<std::vector<T>> res; //the internal vectors are the columns of the CSV file
	std::ifstream file(f_dir);
	if (!file.is_open()) {
		std::cerr << "Error:unable to open file." << std::endl;
		return {};
	}
	std::string row;
	for (int i = 0; i < lines_to_skip; i++) {
		std::getline(file, row);
	}

	while (std::getline(file, row)) {
		if (row.empty()) {continue;}
		std::stringstream stream_row(row);
		std::string string_value;
		size_t k = 0;

		while (std::getline(stream_row, string_value, ',')) {
			T value;
			std::stringstream(string_value) >> value;
			if (k >= res.size()) {
				res.push_back(std::vector<T>());
			}

			res[k].push_back(value);
			k++;
		}
	}
	file.close();
	return res;
}
