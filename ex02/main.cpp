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
		if (left[i] <= right[j])
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
	std::vector<int> arr = {2, 17, 3, 11, 6, 15, 8, 16, 99, 88, 1, 55};
	bool isOddArr = false;
	int lastElem = -1;
	if (arr.size() % 2 != 0)
	{
		int lastElem = arr.back();
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
		{
			int tmp = v[i].first;
			v[i].first = v[i].second;
			v[i].second = tmp;
			// std::swap(v[i].first, v[i].second);
		}
	}
	std::cout << "__1__" << std::endl;
	for (int i = 0; i < v.size(); ++i)
		std::cout << v[i].first << " and " << v[i].second << std::endl;

	fordJohnson(v);

	std::cout << "__1__" << std::endl;
	for (int i = 0; i < v.size(); ++i)
		std::cout << v[i].first << " and " << v[i].second << std::endl;



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
