#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib>

int main(int ac, char **av) 
{
	std::stack<int> s;
	
	std::string input = av[1];

	// check if string is valid

	std::string tkn;
	std::stringstream ss(input);
	while (ss >> tkn) 
	{
		if (tkn == "+" || tkn == "-" || tkn == "*" || tkn == "/") {
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();

			if (tkn == "+")
				s.push(y + x);
			if (tkn == "-")
				s.push(y - x);
			if (tkn == "*")
				s.push(y * x);
			if (tkn == "/")
				s.push(y / x);
		} else {
			int value;
			std::stringstream convert(tkn);
			convert >> value;
			// add check conversion later
			s.push(value);
		}
	}
	std::cout << "Result: " << s.top() << std::endl;

	return 0;
}
