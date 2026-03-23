#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <ctime>

typedef std::pair<int, int> pair;
template <typename Container, typename PairContainer>
class PmergeMe
{
private:
	Container _v;
	int _lastElem;
	int _totalPedants;

	PairContainer pairUp(Container vArr);
	void sortPairs(PairContainer& vPair);
	void merge(PairContainer left, PairContainer right, PairContainer& vPair);
	Container createMainChain(PairContainer& sortedVPair);
	Container calcJacobSeq();
	Container insert(Container& mainChain, PairContainer& vPair, Container jacob);
public:
	PmergeMe();
	PmergeMe(const PmergeMe& rhs);
	PmergeMe& operator=(const PmergeMe& rhs);
	~PmergeMe();
	Container fordJohnson(Container input);
};

// OCF
template <typename Container, typename PairContainer>
PmergeMe<Container, PairContainer>::PmergeMe() : _lastElem(-1)
{
	// std::cout << "[c]PmergeMe" << std::endl;
}
template <typename Container, typename PairContainer>
PmergeMe<Container, PairContainer>::~PmergeMe() 
{
	std::cout << "~PmergeMe" << std::endl;
}

// ---
template <typename Container, typename PairContainer>
Container PmergeMe<Container, PairContainer>::fordJohnson(Container input)
{
	PairContainer vPair = pairUp(input);
	sortPairs(vPair);
	Container mainChain = createMainChain(vPair);
	Container jacob = calcJacobSeq();
	Container finalChain = insert(mainChain, vPair, jacob);
	return finalChain;
}

template <typename Container, typename PairContainer>
PairContainer PmergeMe<Container, PairContainer>::pairUp(Container vArr)
{
	PairContainer vPair;
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

template <typename Container, typename PairContainer>
void PmergeMe<Container, PairContainer>::sortPairs(PairContainer& vPair)
{
	int n = vPair.size();
	if (n < 2)
		return ;
	int mid = n / 2;
	PairContainer left(mid);
	PairContainer right(n-mid);

	for (int i = 0; i < mid; ++i)
		left[i] = vPair[i];
	for (int i = mid; i < n; ++i)
		right[i - mid] = vPair[i];
	sortPairs(left);
	sortPairs(right);
	merge(left, right, vPair);
}

template <typename Container, typename PairContainer>
void PmergeMe<Container, PairContainer>::merge(PairContainer left, PairContainer right, PairContainer& vPair)
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

template <typename Container, typename PairContainer>
Container PmergeMe<Container, PairContainer>::createMainChain(PairContainer& sortedVPair)
{
	Container mainChain;
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

template <typename Container, typename PairContainer>
Container PmergeMe<Container, PairContainer>::calcJacobSeq()
{
	Container jacob;
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

template <typename Container, typename PairContainer>
Container PmergeMe<Container, PairContainer>::insert(Container& mainChain, PairContainer& vPair, Container jacob)
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

			typename Container::iterator limit = std::lower_bound(mainChain.begin(), mainChain.end(), parentValue);
			typename Container::iterator insertPoint = std::lower_bound(mainChain.begin(), limit, pedantValue);
			mainChain.insert(insertPoint, pedantValue);
		}
	}
	if (this->_lastElem != -1)
	{
		typename Container::iterator limitLastElem = std::lower_bound(mainChain.begin(), mainChain.end(), this->_lastElem);
		mainChain.insert(limitLastElem, this->_lastElem);
	}
	return mainChain;
}

#endif