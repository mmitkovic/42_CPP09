#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <string>
#include <stack>

class RPN 
{
private:
	std::stack<int> s;
public:
	RPN();
	RPN(const RPN& rhs);
	RPN& operator=(const RPN& rhs);
	~RPN();
	// ---
	class BadFormatting : public std::exception {
	public:
		virtual const char * what() const throw() { return "Error: bad formatting."; }
	};
	class DivisionByZero : public std::exception {
	public:
		virtual const char * what() const throw() { return "Error: division by zero."; }
	};
	void calculate(const std::string& s);
};

#endif
