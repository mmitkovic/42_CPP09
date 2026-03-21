/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:16:05 by mmitkovi          #+#    #+#             */
/*   Updated: 2026/03/21 11:52:55 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <deque>
#include <iostream>
#include "PmergeMe.hpp"


int main(/*int ac, char **av*/)
{
	/* Input Validation
	if (ac < 2)
		std::cerr << "Invalid input" << std::endl;
	*/

	// TODO: validation of the input
	// TODO: printing Before & After
	// TODO: time clac for each container
	std::vector<int> inputV = {2, 7, 13, 1, 888888, 4, 5, 9, 11, 8, 10, 3, 12};
	std::deque<int> inputD = {2, 7, 13, 1, 888888, 4, 5, 9, 11, 8, 10, 3, 12};

	// template <typename Container, typename PairContainer>
	PmergeMe<std::vector<int>, std::vector<pair>> v;
	PmergeMe<std::deque<int>, std::deque<pair>> d;
	// try
	v.fordJohnson(inputV);
	d.fordJohnson(inputD);
	// catch

	return 0;
}
