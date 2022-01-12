#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <climits>
// #include "utilis.cpp"
using namespace std;
using namespace std::chrono;

void insertionSort(vector<int>& v)
{
	for (int i = 0; i < v.size(); ++i) 
	{
		for (int j = i; j > 0 && v[j-1] > v[j]; --j)
		{
			swap(v[j], v[j - 1]);
		}
	}
}