/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:16:05 by mmitkovi          #+#    #+#             */
/*   Updated: 2026/03/23 17:36:17 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <deque>
#include "PmergeMe.hpp"

void sub_timespec(struct timespec& s, struct timespec& e, double& d)
{
	d  = (e.tv_sec - s.tv_sec) * 1e9;
	d = d + (e.tv_nsec - s.tv_nsec);
}

void printBefore(const std::vector<int>& in)
{
	std::cout << "Before: ";
	for (size_t i = 0; i < in.size(); ++i)
		std::cout << in[i] << " ";
	std::cout << std::endl;
}

void printAfter(const std::vector<int>& out)
{
	std::cout << "After: ";
	for (size_t i = 0; i < out.size(); ++i)
		std::cout << out[i] << " ";
	std::cout << std::endl;
}

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

	// Check
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

	// TODO: duplicates allowed?
	
	printBefore(inputV);
	// template <typename Container, typename PairContainer>
	PmergeMe<std::vector<int>, std::vector<pair> > v;
	PmergeMe<std::deque<int>, std::deque<pair> > d;
	
	// Time
	struct timespec startV, endV;
	if (clock_gettime(CLOCK_REALTIME, &startV) == -1)
	{
		std::cerr << "Clock_gettime" << std::endl;
		return 1;
	}
	// ALGO Vector Start
	std::vector<int> outputV = v.fordJohnson(inputV);
	// --- END
	if (clock_gettime(CLOCK_REALTIME, &endV) == -1)
	{
		std::cerr << "Clock_gettime" << std::endl;
		return 1;
	}
	double nanoV;
	sub_timespec(startV, endV, nanoV);

//	PRINT After
	printAfter(outputV);
	struct timespec startD, endD;
	if (clock_gettime(CLOCK_REALTIME, &startD) == -1)
	{
		std::cerr << "Clock_gettime" << std::endl;
		return 1;
	}
	// ALGO Deque Start
	std::deque<int> outputD = d.fordJohnson(inputD);
	// --- END
	if (clock_gettime(CLOCK_REALTIME, &endD) == -1)
	{
		std::cerr << "Clock_gettime" << std::endl;
		return 1;
	}
	double nanoD;
	sub_timespec(startD, endD, nanoD);
	int num_elem = --ac;
	std::cout << std::setprecision(5) <<"Time to process a range of " << num_elem << " elements with std::vector<int> : " 
			<< nanoV/1000 << " μs" << std::endl;
	std::cout << "Time to process a range of " << num_elem << " elements with std::deque<int> : " 
			<< nanoD/1000 << std::setprecision(5) << " μs" << std::endl;


	return 0;
}
