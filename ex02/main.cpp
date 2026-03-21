/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:16:05 by mmitkovi          #+#    #+#             */
/*   Updated: 2026/03/21 17:33:24 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <deque>
#include <iostream>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include "PmergeMe.hpp"


int main(int ac, char **av)
{
	if (ac < 2) 
	{
		std::cerr << "Invalid input" << std::endl;
		return 1;
	}
	std::string input;
	std::vector<int> inputV;
	std::deque<int> inputD;
	for (int i = 1; i < ac; ++i)
	{
		input = av[i];
		for (size_t i = 0; i < input.size(); ++i)
		{
			if (!std::isdigit(input[i]))
			{
				std::cerr << "Not a digit --> [" << input  << "]" << std::endl;
				return 1;
			}
		}
		int num = atoi(input.c_str());
		inputV.push_back(num);
		inputD.push_back(num);
	}
	std::cout << std::endl;

	// TODO: time clac for each container
	
	std::cout << "Before: ";
	for (size_t i = 0; i < inputD.size(); ++i)
		std::cout << inputD[i] << " ";
	std::cout << std::endl;

	// template <typename Container, typename PairContainer>
	PmergeMe<std::vector<int>, std::vector<pair> > v;
	PmergeMe<std::deque<int>, std::deque<pair> > d;
	
	// Time
	const std::clock_t v_start = std::clock();
	// ALGO START
	std::vector<int> outputV = v.fordJohnson(inputV);
	// --- END
	const std::clock_t v_end = std::clock();
	std::cout << std::fixed << std::setprecision(5) << "With std::vector<int>: "
				<< 1000000.0 * (v_end - v_start) / CLOCKS_PER_SEC << " μs" << std::endl;

	// Print the output
	std::cout << "After std::vector<int>: ";
	for (size_t i = 0; i < outputV.size(); ++i)
		std::cout << outputV[i] << " ";
	std::cout << std::endl;

	const std::clock_t d_start = std::clock();
	// Algo Start
	std::deque<int> outputD = d.fordJohnson(inputD);
	const std::clock_t d_end = std::clock();
	std::cout << std::fixed << std::setprecision(5) << "With std::deque<int>: "
				<< 1000000.0 * (d_end - d_start) / CLOCKS_PER_SEC << " μs" << std::endl;
	
	// Print the output
	std::cout << "After std::deque<int>: ";
	for (size_t i = 0; i < outputD.size(); ++i)
		std::cout << outputD[i] << " ";
	std::cout << std::endl;
	// catch

	return 0;
}
