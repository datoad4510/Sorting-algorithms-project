#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <climits>
// 	#include "utilis.cpp"
using namespace std;
using namespace std::chrono;

vector<int> merge(vector<int>& v1, vector<int>& v2)
{
	vector<int> v3;
	int size3 = v1.size() + v2.size();

	//sentinel variables
	v1.push_back(INT_MAX);
	v2.push_back(INT_MAX);

	// indices for v1 and v2
	int j = 0;
	int k = 0;

	for (int i = 0; i < size3; i++)
	{
		if (v1[j] <= v2[k])
		{
			v3.push_back(v1[j]);
			++j;
		}
		else
		{
			v3.push_back(v2[k]);
			++k;
		}
	}
	v1.pop_back();//removing sentinels
	v2.pop_back();
	return v3;
}

vector<int> mergesort(vector<int>& v)
{
	int q = v.size() / 2;
	if (q == 0)
		return v; //base case

	// divide array into two subarrays
	vector<int> v1(v.begin(), v.begin() + q);
	vector<int> v2(v.begin() + q, v.end());

	v1 = mergesort(v1);
	v2 = mergesort(v2);

	return merge(v1, v2);
}

void mergesortHelper(vector<int>& v)
{
	v = mergesort(v);
}
