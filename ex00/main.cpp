#include <cctype>
#include <exception>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

std::map<std::string, double> readCSV(const char * filename)
{
	std::ifstream file(filename, std::ios::in);
	if (!file.is_open())
		throw std::exception();
	std::map<std::string, double> data;
	std::string lineStr;
	while (std::getline(file, lineStr))
	{
		// split string
		/*
			* Consume first line?
		*/
		size_t index = lineStr.find(",");
		if (index != std::string::npos)
		{
			std::string dateK = lineStr.substr(0, index);
			double rateV;
			// convert to double
			std::stringstream ss(lineStr.substr(index+1, lineStr.size()-1));
			if (!(ss >> rateV))
			{
				std::cout << "Error: " << lineStr << std::endl;
				continue;
			}
			data[dateK] = rateV;
		}
		else {
			std::cout << "Invalid data" << std::endl;
		}
	}
	file.close();
	return data;
}

int main(int ac, char ** av)
{
	if (ac != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	const char * inputFileName = av[1];
	std::map<std::string, double> data;
	try {
		data = readCSV("data.csv");
	} catch ( const std::ifstream::failure& e) {
		std::cerr << "Error: could not open file. " <<  std::endl;
	}
	/*
	// reading map
	std::map<std::string, double>::const_iterator it = data.begin();
	std::map<std::string, double>::const_iterator ite = data.end();
	while (it != ite) 
	{
		std::cout << "K: " << it->first << " | " << "V: " << it->second << std::endl;;
		++it;
	}
	*/

	// input.txt read
	std::ifstream input(inputFileName);
	if (!input.is_open())
		throw std::exception();

	std::string lineInputFile;
	while (std::getline(input, lineInputFile))
	{
		lineInputFile.erase(std::remove(lineInputFile.begin(), lineInputFile.end(), ' '), lineInputFile.end());
		size_t index = lineInputFile.find("|");
		if (index != std::string::npos)
		{
			std::string inputDate = lineInputFile.substr(0, index);
			double inputRate;
			std::stringstream ss(lineInputFile.substr(index+1, lineInputFile.size()-1));
			if (!(ss >> inputRate))
			{
				std::cout << "Rate Error: " << lineInputFile << std::endl;
				continue;
			}
			std::map<std::string, double>::iterator it = data.lower_bound(inputDate);
			if (it != data.end() && it->first != inputDate) {
				--it;
				if (it != data.end()) {
					double res = it->second * inputRate;
					std::cout << inputDate << " => " << inputRate << " = " << res << std::endl;
				}
			}
			else if (it != data.end() && it->first == inputDate) {
				double res = it->second * inputRate;
				std::cout << inputDate << " => " << inputRate << " = " << res << std::endl;
			}
			else
				std::cout << "Not present" << std::endl;
		}
		else
		{
			std::cerr << "Error: bad input => " << lineInputFile << std::endl;
		}
		
	}

	return 0;
}
