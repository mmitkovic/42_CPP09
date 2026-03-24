#include <iostream>
#include "PmergeMe.hpp"

typedef std::pair<int, int> pair;
PmergeMe::PmergeMe() : _lastElem(-1)
{
	std::cout << "[c]PmergeMe" << std::endl;
}
PmergeMe::PmergeMe(const PmergeMe& rhs) : _lastElem(rhs._lastElem), _totalPedants(rhs._totalPedants)
{
	std::cout << "[c][c]PmergeMe" << std::endl;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
	std::cout << "[c][a][o]PmergeMe" << std::endl;
	if (this != &rhs)
	{
		this->_lastElem = rhs._lastElem;
		this->_totalPedants = rhs._totalPedants;
	}
	return *this;
}
PmergeMe::~PmergeMe()
{
	std::cout << "~PmergeMe" << std::endl;
}

// --- Vector implementation
std::vector<int> PmergeMe::fordJohnson(std::vector<int> input)
{
	std::vector<pair> vPair = pairUp(input);
	sortPairs(vPair);
	std::vector<int> mainChain = createMainChain(vPair);
	std::vector<int> jacob;
	calcJacobSeq(jacob);
	std::vector<int> finalChain = insert(mainChain, vPair, jacob);
	return finalChain;
}

std::vector<pair> PmergeMe::pairUp(std::vector<int> vArr)
{
	std::vector<pair> vPair;
	if (vArr.size() % 2 != 0)
	{
		this->_lastElem = vArr.back();
		vArr.pop_back();
	}
	for (size_t i = 0; i < vArr.size(); ++i)
	{
		if (i % 2 == 0)
		{
			int a = vArr[i];
			int b = vArr[i+1];
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

void PmergeMe::calcJacobSeq(std::vector<int>& jacob)
{
	jacob.push_back(0);
	jacob.push_back(1);
	int i = 1;
	while (jacob.back() < this->_totalPedants) 
	{
		jacob.push_back(jacob[i] + 2 * jacob[i-1]);
		i++;
	}
}

std::vector<int> PmergeMe::insert(std::vector<int>& mainChain, std::vector<pair>& vPair, std::vector<int> jacob)
{
	for (size_t i = 3; i < jacob.size(); ++i)
	{
		size_t current_jacob = jacob[i];
		size_t previouse_jacob = jacob[i-1];

		if (current_jacob > vPair.size())
			current_jacob = vPair.size();
		for (size_t k = current_jacob; k > previouse_jacob; --k)
		{
			int pedantValue = vPair[k-1].second;
			int parentValue = vPair[k-1].first;

			std::vector<int>::iterator limit = std::lower_bound(mainChain.begin(), mainChain.end(), parentValue);
			std::vector<int>::iterator insertPoint = std::lower_bound(mainChain.begin(), limit, pedantValue);
			mainChain.insert(insertPoint, pedantValue);
		}
	}
	if (this->_lastElem != -1)
	{
		std::vector<int>::iterator limitLastElem = std::lower_bound(mainChain.begin(), mainChain.end(), this->_lastElem);
		mainChain.insert(limitLastElem, this->_lastElem);
	}
	return mainChain;
}

// --- Deque implementation
std::deque<int> PmergeMe::fordJohnson(std::deque<int> input)
{
	std::deque<pair> vPair = pairUp(input);
	sortPairs(vPair);
	std::deque<int> mainChain = createMainChain(vPair);
	std::deque<int> jacob;
	calcJacobSeq(jacob);
	std::deque<int> finalChain = insert(mainChain, vPair, jacob);
	return finalChain;
}

std::deque<pair> PmergeMe::pairUp(std::deque<int> vArr)
{
	std::deque<pair> vPair;
	if (vArr.size() % 2 != 0)
	{
		this->_lastElem = vArr.back();
		vArr.pop_back();
	}
	for (size_t i = 0; i < vArr.size(); ++i)
	{
		if (i % 2 == 0)
		{
			int a = vArr[i];
			int b = vArr[i+1];
			vPair.push_back(std::make_pair(a, b));
		}
	}
	for (size_t i = 0; i < vPair.size(); ++i)
		if (vPair[i].first < vPair[i].second)
			std::swap(vPair[i].first, vPair[i].second);
	return vPair;
}

void PmergeMe::sortPairs(std::deque<pair>& vPair)
{
	int n = vPair.size();
	if (n < 2)
		return ;
	int mid = n / 2;
	std::deque<pair> left(mid);
	std::deque<pair> right(n-mid);

	for (int i = 0; i < mid; ++i)
		left[i] = vPair[i];
	for (int i = mid; i < n; ++i)
		right[i - mid] = vPair[i];
	sortPairs(left);
	sortPairs(right);
	merge(left, right, vPair);
}

void PmergeMe::merge(std::deque<pair> left, std::deque<pair> right, std::deque<pair>& vPair)
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

std::deque<int> PmergeMe::createMainChain(std::deque<pair>& sortedVPair)
{
	std::deque<int> mainChain;
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

void PmergeMe::calcJacobSeq(std::deque<int>& jacob)
{
	jacob.push_back(0);
	jacob.push_back(1);
	int i = 1;
	while (jacob.back() < this->_totalPedants) 
	{
		jacob.push_back(jacob[i] + 2 * jacob[i-1]);
		i++;
	}
}

std::deque<int> PmergeMe::insert(std::deque<int>& mainChain, std::deque<pair>& vPair, std::deque<int> jacob)
{
	for (size_t i = 3; i < jacob.size(); ++i)
	{
		size_t current_jacob = jacob[i];
		size_t previouse_jacob = jacob[i-1];

		if (current_jacob > vPair.size())
			current_jacob = vPair.size();
		for (size_t k = current_jacob; k > previouse_jacob; --k)
		{
			int pedantValue = vPair[k-1].second;
			int parentValue = vPair[k-1].first;

			std::deque<int>::iterator limit = std::lower_bound(mainChain.begin(), mainChain.end(), parentValue);
			std::deque<int>::iterator insertPoint = std::lower_bound(mainChain.begin(), limit, pedantValue);
			mainChain.insert(insertPoint, pedantValue);
		}
	}
	if (this->_lastElem != -1)
	{
		std::deque<int>::iterator limitLastElem = std::lower_bound(mainChain.begin(), mainChain.end(), this->_lastElem);
		mainChain.insert(limitLastElem, this->_lastElem);
	}
	return mainChain;
}
