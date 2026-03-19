/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:15:21 by mmitkovi          #+#    #+#             */
/*   Updated: 2026/03/19 19:15:22 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <map>

// OCF
BitcoinExchange::BitcoinExchange() {
	std::cout << "[c]btc" << std::endl;
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs) : _database(rhs._database) {
	std::cout << "[c][c]btc" << std::endl;
}
BitcoinExchange::BitcoinExchange(const char * dbPath)
{
	std::cout << "[p][c]btc" << std::endl;
	_loadDatabase(dbPath);
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
	std::cout << "[c][a][o]btc" << std::endl;
	if (this != & rhs) {
		this->_database = rhs._database;
	}
	return *this;
}
BitcoinExchange::~BitcoinExchange() {
	std::cout << "~btc" << std::endl;
}

// ---
bool BitcoinExchange::isValidValue(const double v) {
	if (v < 0 || v > 1000)
		return false;
	return true;
}
bool BitcoinExchange::checkYear(const std::string& y, dateStruct& dates)
{
	for (size_t i = 0; i < y.size(); ++i) {
		if (!std::isdigit(y[i]))
			return false;
	}
	std::stringstream ss(y);
	if (!(ss >> dates.year))
		return false;
	if (dates.year < 2009 || dates.year > 2026)
		return false;
	return true;
}
bool BitcoinExchange::checkMonth(const std::string& m, dateStruct& dates)
{
	for (size_t i = 0; i < m.size(); ++i) {
		if (!std::isdigit(m[i]))
			return false;
	}
	std::stringstream ss(m);
	if (!(ss >> dates.month))
		return false;
	if (dates.month < 1 || dates.month > 12)
		return false;
	return true;
}
bool BitcoinExchange::checkDay(const std::string& d, dateStruct& dates)
{
	for (size_t i = 0; i < d.size(); ++i) {
		if (!std::isdigit(d[i]))
			return false;
	}
	std::stringstream ss(d);
	if (!(ss >> dates.day))
		return false;
	if (dates.day < 1)
		return false;
	bool leapYear = false;
	if (dates.year % 4 == 0 && (dates.year % 100 > 0 || dates.year % 400 == 0))
		leapYear = true;
	int maxDays;
	switch (dates.month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			maxDays  = 31;
			break;
		case 2:
			if (leapYear)
				maxDays = 29;
			else
				maxDays = 28;
			break;
		case 4: case 6: case 9: case 11:
			maxDays = 30;
			break;
		default:
			return false;
	}
	if (dates.day > maxDays)
		return false;

	return true;
}
bool BitcoinExchange::isValidDate(const std::string& date)
{
	size_t iY = date.find("-");
	if (iY != std::string::npos) {
		BitcoinExchange::dateStruct dates = { 0, 0, 0 };
		std::string yearStr = date.substr(0, iY);
		if (!checkYear(yearStr, dates))
			return false;
		size_t iM = date.find_last_of("-");
		if (iM != std::string::npos) {
			std::string monthStr = date.substr(iY+1, iM-(iY+1));
			if (!checkMonth(monthStr, dates))
				return false;
		}
		else
			return false;
		std::string dayStr = date.substr(iM+1, date.size()-1);
		if (!checkDay(dayStr, dates))
			return false;
		return true;
	}
	else
		return false;
}

void BitcoinExchange::_loadDatabase(const char * filename)
{
	// Load CSV
	std::ifstream file(filename, std::ios::in);
	if (!file.is_open())
		throw FileNotFound();
	std::string header;
	if (std::getline(file, header)) {
		(void)header;
	}
	std::string lineStr;
	while (std::getline(file, lineStr))
	{
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
			_database[dateK] = rateV;
		}
		else {
			std::cout << "Invalid data" << std::endl;
		}
	}
	file.close();
}

void BitcoinExchange::calculate(const char * inputPath) {
	
	std::ifstream input(inputPath);
	if (!input.is_open())
		throw FileNotFound();
	std::string header;
	if (std::getline(input, header)) {
		(void)header;
	}
	std::string lineInputFile;
	while (std::getline(input, lineInputFile))
	{
		lineInputFile.erase(std::remove(lineInputFile.begin(), lineInputFile.end(), ' '), lineInputFile.end());
		size_t index = lineInputFile.find("|");
		try {
			if (index != std::string::npos) {
				std::string inputDate = lineInputFile.substr(0, index);
				try {
					if (!isValidDate(inputDate))
						throw BadInput();
				} catch (const std::exception& e) {
					std::cout << e.what() << inputDate << std::endl;
					continue;
				}
				double inputRate;
				std::stringstream ss(lineInputFile.substr(index+1, lineInputFile.size()-1));
				try {
					if (!(ss >> inputRate)) {
						throw BadInput();
					}
				} catch (const std::exception& e) {
					std::cerr << e.what() << lineInputFile.substr(index+1, lineInputFile.size()-1) << std::endl;
					continue;
				}
				if (isValidValue(inputRate)) {
					std::map<std::string, double>::iterator it = _database.lower_bound(inputDate);
					if (it->first != inputDate)
						--it;
					if (it != _database.end()) {
						double res = it->second * inputRate;
						std::cout << inputDate << " => " << inputRate << " = " << res << std::endl;
					}
				} else {
					try {
						if (inputRate < 0)
							throw NegativeNumber();
							// std::cout <<  << std::endl;
						else if (inputRate > 1000)
							throw LargeNumber();
						// std::cout <<  << std::endl;
					} catch (const std::exception& e) {
						std::cout << e.what() << std::endl;
					}
				}
			}
			else
				throw BadInput();
		} catch (const std::exception& e) {
			std::cerr << e.what() << lineInputFile << std::endl;
		}
	}
}
