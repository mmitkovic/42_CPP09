/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:16:05 by mmitkovi          #+#    #+#             */
/*   Updated: 2026/03/19 20:26:23 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include "PmergeMe.hpp"


int main(/*int ac, char **av*/)
{
	/* Input Validation
	if (ac < 2)
		std::cerr << "Invalid input" << std::endl;
	*/
	std::vector<int> input = {2, 7, 13, 1, 6, 4, 5, 9, 11, 8, 10, 3, 12};

	PmergeMe v;
	// try
	v.fordJohnson(input);
	// catch

	return 0;
}
