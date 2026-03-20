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

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
typedef std::vector<std::pair<int, int> > pair;
std::vector<std::pair<int, int> > merge(pair left, pair right, pair& arr )
{
	int nL = left.size();
	int nR = right.size();
	int i = 0, j = 0, k = 0;
	while (i < nL && j < nR)
	{
		if (left[i].first <= right[j].first)
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < nL) 
	{
		arr[k] = left[i];
		i++;
		k++;
	}
	while (j < nR)
	{
		arr[k] = right[j];
		j++;
		k++;
	}
	return arr;
}

void fordJohnson(std::vector<std::pair<int, int> >& v)
{
	int n = v.size();
	if (n < 2)
		return ;
	int mid = n / 2;
	std::vector<std::pair<int, int> > left(mid);
	std::vector<std::pair<int, int> > right(n-mid);

	for (int i = 0; i < mid; ++i)
		left[i] = v[i];
	for (int i = mid; i < n; ++i)
		right[i - mid] = v[i];
	fordJohnson(left);
	fordJohnson(right);
	merge(left, right, v);
}

int main()
{
	std::vector<std::pair<int, int> > v;
	std::vector<int> arr = {2, 17, 3, 11, 6, 15, 8, 16, 99, 88, 1, 55, 4};
	bool isOddArr = false;
	int lastElem = -1;
	if (arr.size() % 2 != 0)
	{
		lastElem = arr.back();
		isOddArr = true;
		arr.pop_back();
	}
	for (int i = 0; i < arr.size(); ++i)
	{
		if (i % 2 == 0)
		{
			int a = arr[i];
			i++;
			int b = arr[i];
			v.push_back(std::make_pair(a, b));
		}
	}
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i].first < v[i].second)
			std::swap(v[i].first, v[i].second);
	}
	std::cout << "__Before__" << std::endl;
	for (int i = 0; i < v.size(); ++i)
		std::cout << v[i].first << " and " << v[i].second << std::endl;

	fordJohnson(v);

	std::cout << "__After__" << std::endl;
	for (int i = 0; i < v.size(); ++i)
		std::cout << v[i].first << " and " << v[i].second << std::endl;

	// Creating Main Chain
	std::vector<int> finalChain;
	int totalPedants = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		if (i == 0)
			finalChain.push_back(v[i].second);
		finalChain.push_back(v[i].first);
		totalPedants++;
	}
	if (lastElem != -1)
		totalPedants++;

	// Calculation Jaconsthal sequence
	std::vector<int> jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	int i = 1;
	while (jacob.back() < totalPedants) {
		jacob.push_back(jacob[i] + 2 * jacob[i-1]);
		i++;
	}

	// Insertion logic
	for (int i = 3; i < jacob.size(); ++i)
	{
		int current_jacob = jacob[i];
		int previouse_jacob = jacob[i-1];

		if (current_jacob > v.size())
			current_jacob = v.size();
		// Inner Loop: Count BACKWARDS through the group
		for (int k = current_jacob; k > previouse_jacob; --k)
		{
			// Because 'k' represents the mathematical number (e.g., 3 for b_3),
			// its actual index in vector 'v' is k - 1.
			int pedantValue = v[k-1].second;
			int parentValue = v[k-1].first;

			// --- BINARY & INSERTION GOES HERE ---
			std::vector<int>::iterator limit = std::lower_bound(finalChain.begin(), finalChain.end(), parentValue);
			std::vector<int>::iterator insertPoint = std::lower_bound(finalChain.begin(), limit, pedantValue);
			finalChain.insert(insertPoint, pedantValue);
		}
	}
	// Last Elem insert
	if (lastElem != -1)
	{
		std::vector<int>::iterator limitLastElem = std::lower_bound(finalChain.begin(), finalChain.end(), lastElem);
		finalChain.insert(limitLastElem, lastElem);
	}

	//Final chain print
	std::cout << "Final Chain: ";
	for (int i = 0; i < finalChain.size(); ++i)
	{
		std::cout << finalChain[i] << " ";
	}
	std::cout << std::endl;

	/* Jacobsthal Sequence print
	std::cout << "___Jacobsthal___" << std::endl;
	for (int i = 0; i < jacob.size(); ++i) {
		std::cout << jacob[i] << " ";
	}
	std::cout << std::endl;
	*/



	/* Printing Addresses
	std::vector<std::pair<int, int> >::iterator it = v.begin();
	for (int i = 0; i < v.size(); ++i) {
		std::cout << &v[i] << " and " << &v[i] << std::endl;
		std::cout << &(*it)+i << std::endl;
		std::cout << "----" << std::endl;
	}
	std::cout << (v[0].second < v[1].second) << std::endl;
	*/
}
