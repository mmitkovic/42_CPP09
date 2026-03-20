/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:21:25 by mmitkovi          #+#    #+#             */
/*   Updated: 2026/03/19 19:21:26 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

// OCF
PmergeMe::PmergeMe() {
	std::cout << "[c]PmergeMe" << std::endl;
}
PmergeMe::~PmergeMe() {
	std::cout << "~PmergeMe" << std::endl;
}

// ---
void PmergeMe::fordJohnson(std::vector<int> input)
{
	std::vector<pair> vPair = pairUp(input);
	sortPairs(vPair);
	std::vector<int> mainChain = createMainChain(vPair);
	std::vector<int> jacob = calcJacobSeq();
	std::vector<int> finalChain = insert(mainChain, vPair, jacob);

	//Final chain print
	std::cout << "Final Chain: ";
	for (size_t i = 0; i < finalChain.size(); ++i)
	{
		std::cout << finalChain[i] << " ";
	}
	std::cout << std::endl;

	
}
std::vector<pair> PmergeMe::pairUp(std::vector<int> vArr)
{
	std::vector<pair> vPair;
	//bool isOddArr = false;
	if (vArr.size() % 2 != 0)
	{
		this->_lastElem = vArr.back();
		//isOddArr = true;
		vArr.pop_back();
	}
	for (size_t i = 0; i < vArr.size(); ++i)
	{
		if (i % 2 == 0)
		{
			int a = vArr[i];
			i++;
			int b = vArr[i];
			vPair.push_back(std::make_pair(a, b));
		}
	}
	for (size_t i = 0; i < vPair.size(); ++i)
		if (vPair[i].first < vPair[i].second)
			std::swap(vPair[i].first, vPair[i].second);
	return vPair;
}

void PmergeMe::sortPairs(std::vector<pair>& vPair)
{
	int n = vPair.size();
	if (n < 2)
		return ;
	int mid = n / 2;
	std::vector<pair> left(mid);
	std::vector<pair> right(n-mid);

	for (int i = 0; i < mid; ++i)
		left[i] = vPair[i];
	for (int i = mid; i < n; ++i)
		right[i - mid] = vPair[i];
	sortPairs(left);
	sortPairs(right);
	merge(left, right, vPair);
}
	
void PmergeMe::merge(std::vector<pair> left, std::vector<pair> right, std::vector<pair>& vPair)
{
	int nL = left.size();
	int nR = right.size();
	int i = 0, j = 0, k = 0;
	while (i < nL && j < nR)
	{
		if (left[i].first <= right[j].first)
		{
			vPair[k] = left[i];
			i++;
		}
		else
		{
			vPair[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < nL) 
	{
		vPair[k] = left[i];
		i++;
		k++;
	}
	while (j < nR)
	{
		vPair[k] = right[j];
		j++;
		k++;
	}
}

std::vector<int> PmergeMe::createMainChain(std::vector<pair>& sortedVPair)
{
	std::vector<int> mainChain;
	this->_totalPedants = 0;
	for (size_t i = 0; i < sortedVPair.size(); ++i)
	{
		if (i == 0)
			mainChain.push_back(sortedVPair[i].second);
		mainChain.push_back(sortedVPair[i].first);
		this->_totalPedants++;
	}
	if (this->_lastElem != -1)
		this->_totalPedants++;

	return mainChain;
}

std::vector<int> PmergeMe::calcJacobSeq()
{
	std::vector<int> jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	int i = 1;
	while (jacob.back() < this->_totalPedants) 
	{
		jacob.push_back(jacob[i] + 2 * jacob[i-1]);
		i++;
	}
	return jacob;
}

std::vector<int> PmergeMe::insert(std::vector<int>& mainChain, std::vector<pair>& vPair, std::vector<int> jacob)
{
	// v -> sorted vector<pair>
	for (size_t i = 3; i < jacob.size(); ++i)
	{
		size_t current_jacob = jacob[i];
		size_t previouse_jacob = jacob[i-1];

		if (current_jacob > vPair.size())
			current_jacob = vPair.size();
		// Inner Loop: Count BACKWARDS through the group
		for (size_t k = current_jacob; k > previouse_jacob; --k)
		{
			// Because 'k' represents the mathematical number (e.g., 3 for b_3),
			// its actual index in vector 'v' is k - 1.
			int pedantValue = vPair[k-1].second;
			int parentValue = vPair[k-1].first;

			// --- BINARY & INSERTION GOES HERE ---
			std::vector<int>::iterator limit = std::lower_bound(mainChain.begin(), mainChain.end(), parentValue);
			std::vector<int>::iterator insertPoint = std::lower_bound(mainChain.begin(), limit, pedantValue);
			mainChain.insert(insertPoint, pedantValue);
		}
	}
	// Last Elem insert
	if (this->_lastElem != -1)
	{
		std::vector<int>::iterator limitLastElem = std::lower_bound(mainChain.begin(), mainChain.end(), this->_lastElem);
		mainChain.insert(limitLastElem, this->_lastElem);
	}
	return mainChain;
}
