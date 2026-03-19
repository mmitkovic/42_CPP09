//#include <pair>
#include <iostream>
#include <utility>
#include <vector>

/*std::vector<std::pair<int, int> >*/ void fordJohnson(std::vector<std::pair<int, int> > v)
{
	// std::vector<std::pair<int, int> > newV;
	for (int i = 0; i < v.size(); ++i)
	{
		//std::cout << v[i].first << std::endl;
		if (v[i].first > v[i+1].first)
			std::swap(v[i], v[i+1]);
		std::cout << v[i].first << " - " << v[i].second << std::endl;
	}
}

int main()
{
	std::vector<std::pair<int, int> > v;
	std::vector<int> arr = {2, 17, 3, 11, 6, 15, 8, 16, 99, 88};
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
