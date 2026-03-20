#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
typedef std::pair<int, int> pair;
class PmergeMe 
{
private:
	std::vector<int> _v;
	int _lastElem = -1;
	int _totalPedants;


	std::vector<pair> pairUp(std::vector<int> vArr);
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

#endif
