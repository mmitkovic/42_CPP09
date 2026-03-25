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

#include <ctime>
#include <iostream>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <deque>
#include <limits.h>
#include "PmergeMe.hpp"

struct timespec time_start()
{
	struct timespec start;
	if (clock_gettime(CLOCK_REALTIME, &start) == -1)
	{
		std::cerr << "Clock_gettime" << std::endl;
		exit(1);
	}
	return start;
}

struct timespec end_time()
{
	struct timespec end;
	if (clock_gettime(CLOCK_REALTIME, &end) == -1)
	{
		std::cerr << "Clock_gettime" << std::endl;
		exit(1);
	}
	return end;
}

double sub_timespec(struct timespec& s, struct timespec& e)
{
	double d;
	d  = (e.tv_sec - s.tv_sec) * 1e9;
	d = d + (e.tv_nsec - s.tv_nsec);
	return d;
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

bool isValidInput(int ac, char **av, std::vector<int>& inputV, std::deque<int>& inputD)
{
	std::string input;
	for (int i = 1; i < ac; ++i)
	{
		input = av[i];
		size_t j = (input[0] == '+') ? 1 : 0;
		while (j < input.size())
		{
			if (!std::isdigit(input[j]))
				return false;
			j++;
		}
		int num = atoi(input.c_str());
		if (num > INT_MAX || num < 0)
			return false;
		inputV.push_back(num);
		inputD.push_back(num);
	}
	return true;
}

int main(int ac, char **av)
{
	if (ac < 2) 
	{
		std::cerr << "Invalid input" << std::endl;
		return 1;
	}
	std::vector<int> inputV;
	std::deque<int> inputD;
	
	// TIME Start Vector
	struct timespec parseStart = time_start();
	// Check input
	if (!isValidInput(ac, av, inputV, inputD))
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	struct timespec parseEnd = end_time();
	double parseTime = sub_timespec(parseStart, parseEnd);
	std::cout << std::setprecision(5) << "Parse time: " << parseTime/1000 << std::endl;

	printBefore(inputV);
	PmergeMe v;
	PmergeMe d;


	struct timespec startV = time_start();
	// ALGO Vector Start
	std::vector<int> outputV = v.fordJohnson(inputV);
	// --- END
	struct timespec endV = end_time();
	double nanoV = sub_timespec(startV, endV);


	struct timespec startD = time_start();
	// ALGO Deque Start
	std::deque<int> outputD = d.fordJohnson(inputD);
	// --- END
	struct timespec endD = end_time();
	double nanoD = sub_timespec(startD, endD);

	printAfter(outputV);
	int num_elem = --ac;
	std::cout << std::setprecision(5) <<"Time to process a range of " << num_elem << " elements with std::vector<int> : " 
			<< (nanoV+parseTime)/1000 << " μs" << std::endl;
	std::cout << "Time to process a range of " << num_elem << " elements with std::deque<int> : " 
			<< (nanoD+parseTime)/1000 << std::setprecision(5) << " μs" << std::endl;
	return 0;
}
