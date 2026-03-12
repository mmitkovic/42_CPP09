#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

typedef struct Dates {
	int year, month, day;
} dateStruct;

class BitcoinExchange
{
private:
	std::map<std::string, double> _database;
	void _loadDatabase(const char * dbPath);
	bool isValidDate(const std::string& date);
	bool isValidValue(const double v);
	bool checkYear(const std::string& y);
	bool checkMonth(const std::string& m);
	bool checkDay(const std::string& d);
public:
	BitcoinExchange();
	BitcoinExchange(const char * dbPath);
	BitcoinExchange(const BitcoinExchange& rhs);
	BitcoinExchange& operator=(const BitcoinExchange& rhs);
	~BitcoinExchange();

	void calculate(const char * inputPath);
};

#endif
