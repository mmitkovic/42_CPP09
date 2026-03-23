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
#include <sys/time.h>
#include <time.h>
#include "PmergeMe.hpp"

void sub_timespec(struct timespec& s, struct timespec& e, double& d)
{
	d  = (e.tv_sec - s.tv_sec) * 1e9;
	d = d + (e.tv_nsec - s.tv_nsec);
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
	
	std::cout << "Before: ";
	for (size_t i = 0; i < inputD.size(); ++i)
		std::cout << inputD[i] << " ";
	std::cout << std::endl;

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
	// ALGO START
	std::vector<int> outputV = v.fordJohnson(inputV);
	// --- END
	
	clock_gettime(CLOCK_REALTIME, &endV);
	double nanoV;
	sub_timespec(startV, endV, nanoV);


	// Print the output
	std::cout << "After std::vector<int>: ";
	for (size_t i = 0; i < outputV.size(); ++i)
		std::cout << outputV[i] << " ";
	std::cout << std::endl;

	//struct timeval startD,endD;
	//gettimeofday(&startD, NULL);

	struct timespec startD, endD;
	if (clock_gettime(CLOCK_REALTIME, &startD) == -1)
	{
		std::cerr << "Clock_gettime" << std::endl;
		return 1;
	}
	// ALGO Deque Start
	std::deque<int> outputD = d.fordJohnson(inputD);

	clock_gettime(CLOCK_REALTIME, &endD);
	double nanoD;
	sub_timespec(startD, endD, nanoD);

	// Print the output
	std::cout << "After std::deque<int>: ";
	for (size_t i = 0; i < outputD.size(); ++i)
		std::cout << outputD[i] << " ";
	std::cout << std::endl;
	
	std::cout << std::fixed << std::setprecision(5) <<"Time to process a range of __ elements with std::vector<int> : " 
			<< nanoV/1000 << " μs" << std::endl;
	std::cout << "Time to process a range of __ elements with std::deque<int> : " 
			<< nanoD/1000 << std::setprecision(5) << " μs" << std::endl;


	return 0;
}
