#include <cctype>
#include <exception>
#include <iostream>
#include <cstdlib>
#include "RPN.hpp"

int main(int ac, char **av) 
{
	if (ac != 2)
	{
		std::cerr << "Error: argument count." << std::endl;
		return 1;
	}
	//std::string input = av[1];
	RPN rpn;
	try {
		rpn.calculate(av[1]);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	/*
	 * TODO: test cc and cao
	 * */
	return 0;
}
