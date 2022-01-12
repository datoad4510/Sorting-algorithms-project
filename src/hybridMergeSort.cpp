#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <climits>
// #include "utilis.cpp"
using namespace std;
using namespace std::chrono;

void insertionSort2(vector<int>& v, int left, int right)
{
	for (int i = left; i < right; ++i)
	{
		for (int j = i; j > 0 && v[j - 1] > v[j]; --j)
		{
			swap(v[j], v[j - 1]);
		}
	}
}

// https://stackoverflow.com/questions/13906169/when-is-insertion-sort-faster-than-merge-sort
vector<int> hybridMergesort(vector<int>& v)
{
	if (v.size() <= 43)
	{
		insertionSort2(v, 0, v.size());
		return v;
	}

	int q = v.size() / 2;
	if (q == 0)
		return v; //base case

	// divide array into two subarrays
	vector<int> v1(v.begin(), v.begin() + q);
	vector<int> v2(v.begin() + q, v.end());

	v1 = hybridMergesort(v1);
	v2 = hybridMergesort(v2);

	return merge(v1, v2);
}

void hybridMergesortHelper(vector<int>& v)
{
	v = hybridMergesort(v);
}