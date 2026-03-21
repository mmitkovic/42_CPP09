#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
typedef std::pair<int, int> pair;
template <typename Container, typename PairContainer>
class PmergeMe
{
private:
	std::vector<int> _v;
	int _lastElem;
	int _totalPedants;

	//std::vector<pair> pairUp(std::vector<int> vArr);
	PairContainer pairUp(Container vArr);
	void sortPairs(std::vector<pair>& vPair);
	void merge(std::vector<pair> left, std::vector<pair> right, std::vector<pair>& vPair);
	std::vector<int> createMainChain(std::vector<pair>& sortedVPair);
	std::vector<int> calcJacobSeq();
	std::vector<int> insert(std::vector<int>& mainChain, std::vector<pair>& vPair, std::vector<int> jacob);
public:
	PmergeMe();
	PmergeMe(const PmergeMe& rhs);
	PmergeMe& operator=(const PmergeMe& rhs);
	~PmergeMe();
	void fordJohnson(std::vector<int> input);
};

template <typename Container, typename PairContainer>
PairContainer PmergeMe::pairUp(Container vArr)
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
#endif
