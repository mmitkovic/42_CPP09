#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <ctime>

typedef std::pair<int, int> pair;

class PmergeMe
{
private:
	int _lastElem;
	int _totalPedants;

	// --- Vector overloads ---
	std::vector<pair> pairUp(std::vector<int> vArr);
	void sortPairs(std::vector<pair>& vPair);
	void merge(std::vector<pair> left, std::vector<pair> right, std::vector<pair>& vPair);
	std::vector<int> createMainChain(std::vector<pair>& sortedVPair);
	void calcJacobSeq(std::vector<int>& jacob);
	std::vector<int> insert(std::vector<int>& mainChain, std::vector<pair>& vPair, std::vector<int> jacob);

	// --- Deque overloads ---
	std::deque<pair> pairUp(std::deque<int> vArr);
	void sortPairs(std::deque<pair>& vPair);
	void merge(std::deque<pair> left, std::deque<pair> right, std::deque<pair>& vPair);
	std::deque<int> createMainChain(std::deque<pair>& sortedVPair);
	void calcJacobSeq(std::deque<int>& jacob);
	std::deque<int> insert(std::deque<int>& mainChain, std::deque<pair>& vPair, std::deque<int> jacob);
public:
	// OCF
	PmergeMe();
	PmergeMe(const PmergeMe& rhs);
	PmergeMe& operator=(const PmergeMe& rhs);
	~PmergeMe();

	// entry point
	std::vector<int> fordJohnson(std::vector<int> input);
	std::deque<int> fordJohnson(std::deque<int> input);
};

#endif
