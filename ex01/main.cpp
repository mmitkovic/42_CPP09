#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib>

int main(int ac, char **av) 
{
	if (ac != 2)
	{
		std::cerr << "Error: argument count." << std::endl;
		return 1;
	}
	std::stack<int> s;
	
	std::string input = av[1];
	std::string tkn;
	std::stringstream ss(input);
	while (ss >> tkn)
	{
		if (tkn == "+" || tkn == "-" || tkn == "*" || tkn == "/") {
			if (s.size() < 2)
			{
				std::cout << "Error: formatting" << std::endl;
				return 3;
			}
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
				if (x == 0) {
					std::cerr << "Error: divison by 0" << std::endl;
					return 5;
				}
				s.push(y / x);
			}
		} else {
			int value;
			std::stringstream convert(tkn);
			if (!(convert >> value) || tkn.size() > 1) {
				std::cerr << "Error: token: " << tkn << std::endl;
				return 2;
			}
			s.push(value);
		}
	}
	if (s.size() != 1) {
		std::cerr << "Error: formatting" << std::endl;
		return 4;
	}
	std::cout << "Result: " << s.top() << std::endl;

	return 0;
}
