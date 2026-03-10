//#include <vector>
#include <cctype>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

/* 
std::vector<std::vector<std::string> > readCSV(const std::string& filename)
{
	std::vector<std::vector<std::string>> data;
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return data;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::vector<std::string> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ','))
		{
			row.push_back(cell);
		}
		data.push_back(row);
	}
	file.close();
	return data;
}
*/

std::map<std::string, double> readCSV(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		//return data;
	}
	std::map<std::string, double> data;
	std::string lineStr;
	while (std::getline(file, lineStr))
	{
		// split string
		int index = lineStr.find(",");
		std::string dateK = lineStr.substr(0, index);
		double rateV;
		try {
			rateV = std::stod(lineStr.substr(index+1, lineStr.size()-1));
		} catch (...) {
			continue;
		}
		data[dateK] = rateV;
	}

	return data;
}

int main() {
	/*
	std::vector<std::vector<std::string>> data = readCSV("data.csv");
	for (int i = 0; i < 10; ++i) {
		std::cout << data[i].front() << std::endl;
		std::cout << data[i].back() << std::endl;
	}
	*/

	std::map<std::string, double> data = readCSV("data.csv");
	// reading map
	std::map<std::string, double>::const_iterator it = data.begin();
	std::map<std::string, double>::const_iterator ite = data.end();
	while (it != ite) 
	{
		std::cout << "K: " << it->first << " | " << "V: " << it->second * 2 << std::endl;;
		++it;
	}

	return 0;
}
