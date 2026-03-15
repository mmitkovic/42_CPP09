#include "RPN.hpp"
#include <sstream>
#include <iostream>

RPN::RPN() {
	std::cout << "[c]RPN" << std::endl;
}
RPN::RPN(const RPN& rhs) : s(rhs.s) {
	std::cout << "[c][c]RPN" << std::endl;
}
RPN& RPN::operator=(const RPN& rhs) {
	std::cout << "[c][a][o]RPN" << std::endl;
	if (this != &rhs) {
		this->s = rhs.s;
	}
	return *this;
}
RPN::~RPN() {
	std::cout << "~RPN" << std::endl;
}

void RPN::calculate(const std::string& str) 
{
	std::string tkn;
	std::stringstream ss(str);
	while (ss >> tkn)
	{
		if (tkn == "+" || tkn == "-" || tkn == "*" || tkn == "/") {
			if (s.size() < 2)
				throw BadFormatting();
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();

			if (tkn == "+")
				s.push(y + x);
			else if (tkn == "-")
				s.push(y - x);
			else if (tkn == "*")
				s.push(y * x);
			else if (tkn == "/") {
				if (x == 0)
					throw DivisionByZero();
				s.push(y / x);
			}
		} else {
			int value;
			std::stringstream convert(tkn);
			if (!(convert >> value) || tkn.size() > 1)
				throw BadFormatting();
			s.push(value);
		}
	}
	if (s.size() != 1)
		throw BadFormatting();
	std::cout << "Result: " << s.top() << std::endl;
}
