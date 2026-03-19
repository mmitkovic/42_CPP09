/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:15:31 by mmitkovi          #+#    #+#             */
/*   Updated: 2026/03/19 19:15:32 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <exception>
#include <iostream>
#include <limits.h>
#include "BitcoinExchange.hpp"

int main(int ac, char ** av)
{
	if (ac != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	const char * inputFileName = av[1];

	try {
		BitcoinExchange btc("data.csv");
		btc.calculate(inputFileName);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
