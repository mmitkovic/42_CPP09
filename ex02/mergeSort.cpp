#include <vector>
#include <iostream>

std::vector<int> merge(std::vector<int> left, std::vector<int> right, std::vector<int>& arr)
{
	//std::cout << "---" << std::endl;
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

void mergeSort(std::vector<int>& arr)
{
	int n = arr.size();
	if (n < 2)
		return ;
	int mid = n / 2;
	std::vector<int> left(mid);
	std::vector<int> right(n - mid);
	std::cout << "Mid: " << mid << std::endl;
	for (int i = 0; i < mid; ++i)
		left[i] = arr[i];
	for (int i = mid; i < n; ++i)
		right[i - mid] = arr[i];
	std::cout << "Left: ";
	for (int i = 0; i < left.size(); ++i)
		std::cout << left[i] << " ";
	std::cout << std::endl;
	std::cout << "Right: ";
	for (int i = 0; i < right.size(); ++i)
		std::cout << right[i] << " ";
	std::cout << std::endl;
	mergeSort(left);
	mergeSort(right);
	merge(left, right, arr);
}

int main()
{
	std::vector<int> arr = {2, 4, 1, 6, 8, 5, 3, 7};
	mergeSort(arr);
	std::cout << "___Final___" << std::endl;
	for (int i = 0; i < arr.size(); ++i)
	{
      		std::cout << arr[i] << " ";
	}
	return 0;
}
