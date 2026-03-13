#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <map>
#include <string>

class BitcoinExchange
{
private:
	typedef struct Dates {
	int year, month, day;
	} dateStruct;
	std::map<std::string, double> _database;
	void _loadDatabase(const char * dbPath);
	bool isValidDate(const std::string& date);
	bool isValidValue(const double v);
	bool checkYear(const std::string& y, dateStruct& dates);
	bool checkMonth(const std::string& m, dateStruct& dates);
	bool checkDay(const std::string& d, dateStruct& dates);
public:
	BitcoinExchange();
	BitcoinExchange(const char * dbPath);
	BitcoinExchange(const BitcoinExchange& rhs);
	BitcoinExchange& operator=(const BitcoinExchange& rhs);
	~BitcoinExchange();

	class FileNotFound : public std::exception {
	public:
		virtual const char * what() const throw() { return "Error: file not found."; }
	};
	class BadInput : public std::exception {
	public:
		virtual const char * what() const throw() { return "Error: bad input ===> "; }
	};
	class LargeNumber : public std::exception {
	public:
		virtual const char * what() const throw() { return "Error: too large a number."; }
	};
	class NegativeNumber : public std::exception {
	public:
		virtual const char * what() const throw() { return "Error: not a positive number."; }
	};
	void calculate(const char * inputPath);
};

#endif
